package esiot.module_lab_3_2;


import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.*;
import jssc.*;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci
 *
 */
public class ExtendedSerialCommChannel implements CommChannel, SerialPortEventListener {

	private SerialPort serialPort;
	private BlockingQueue<String> queue;
	private StringBuffer currentMsg = new StringBuffer("");
	private int localIPportEmu;
	private static final int SERVER_PORT = 8080;
	
	private AndroidEmulatorCommChannel androidEmulatorChannel;
	private static final char BT_MESSAGES_ID = '$';

	public ExtendedSerialCommChannel(String port, int rate) throws Exception {
		this(port, rate, SERVER_PORT);
	}
	
	public ExtendedSerialCommChannel(String port, int rate, int localIPportEmu) throws Exception {
		queue = new ArrayBlockingQueue<String>(100);
		this.localIPportEmu = localIPportEmu;
		
		serialPort = new SerialPort(port);
		try {
		    serialPort.openPort();

		    serialPort.setParams(rate,
		                         SerialPort.DATABITS_8,
		                         SerialPort.STOPBITS_1,
		                         SerialPort.PARITY_NONE);

		    serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
		                                  SerialPort.FLOWCONTROL_RTSCTS_OUT);

		    // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
			serialPort.addEventListener(this);

			System.out.println("serial port ok");
			// emulator server
			
			androidEmulatorChannel = new AndroidEmulatorCommChannel(localIPportEmu);
			androidEmulatorChannel.start();
			
		} catch (SerialPortException ex) {
		    System.err.println("Error on writing string to port: " + port);
		    ex.printStackTrace();
		} catch (IOException ex) {
		    System.err.println("Error on installing emu|IP server");
		    ex.printStackTrace();
		}
		

	}

	@Override
	public void sendMsg(String msg) {
		char[] array = (msg+"\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			synchronized (serialPort) {
				serialPort.writeBytes(bytes);
			}
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		// TODO Auto-generated method stub
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
		return !queue.isEmpty();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Handle an event on the serial port. Read the data and print it.
	 */
	public void serialEvent(SerialPortEvent event) {
		/* if there are bytes received in the input buffer */
		if (event.isRXCHAR()) {
            try {
            		String msg = serialPort.readString(event.getEventValue());
            		
            		msg = msg.replaceAll("\r", "");
            		
            		currentMsg.append(msg);
            		
            		boolean goAhead = true;
            		
        			while(goAhead) {
        				String msg2 = currentMsg.toString();
        				int index = msg2.indexOf("\n");
            			if (index >= 0) {
            				
            				if(msg2.getBytes().length > 1 && msg2.getBytes()[index - 1] == BT_MESSAGES_ID) {
            					androidEmulatorChannel.sendMsgToAndroidEmulator(msg2.substring(0, index - 1));
            				} else {
            					queue.put(msg2.substring(0, index));
            				}
            				
            				currentMsg = new StringBuffer("");
            				if (index + 1 < msg2.length()) {
            					currentMsg.append(msg2.substring(index + 1)); 
            				}
            			} else {
            				goAhead = false;
            			}
        			}
        			
            } catch (Exception ex) {
            		ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}


	class AndroidEmulatorCommChannel extends Thread{

		private ServerSocket server;
		private Socket socket;
		
		public AndroidEmulatorCommChannel(int port) throws IOException {
			server = new ServerSocket(port);
		}
		
		@Override
		public void run() {			
			try {				
				socket = server.accept();
				while(true) {
					BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
					String message = in.readLine();
		            sendMsg(message + BT_MESSAGES_ID);
		        }
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		public void sendMsgToAndroidEmulator(String msg) {
			if (socket != null) {
				PrintWriter out;
				try {
					out = new PrintWriter(socket.getOutputStream(), true);
					out.println(msg);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
