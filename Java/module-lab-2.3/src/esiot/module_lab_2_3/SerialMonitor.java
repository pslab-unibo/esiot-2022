package esiot.module_lab_2_3;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import jssc.*;

public class SerialMonitor implements SerialPortEventListener {
	SerialPort serialPort;
	
	public void start(String portName) {
		serialPort = new SerialPort(portName);
		try {
		    serialPort.openPort();

		    serialPort.setParams(SerialPort.BAUDRATE_9600,
		                         SerialPort.DATABITS_8,
		                         SerialPort.STOPBITS_1,
		                         SerialPort.PARITY_NONE);

		    serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
		                                  SerialPort.FLOWCONTROL_RTSCTS_OUT);

		    serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
		}
		catch (SerialPortException ex) {
		    System.out.println("There are an error on writing string to port т: " + ex);
		}
		
		new UserInputReaderAgent(serialPort).start();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public synchronized void close() {
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
	@Override
	public synchronized void serialEvent(SerialPortEvent event) {
        if(event.isRXCHAR() && event.getEventValue() > 0) {
            try {
                String receivedData = serialPort.readString(event.getEventValue());
                System.out.print(receivedData);
            }
            catch (SerialPortException ex) {
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}

	class UserInputReaderAgent extends Thread {
		
		private SerialPort port;

		public UserInputReaderAgent(SerialPort port){
			this.port = port;
		}
		
		public void run(){
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			while (true){
				try {
					String st = reader.readLine();
					port.writeString(st,"UTF-8");
				} catch (Exception ex){
					ex.printStackTrace();
				}
			}
		}
	}


}