package esiot.module_lab_3_2;


/**
 * Esempio di utilizzo del componente ExtendedSerialCommChannel 
 * che permette lo scambio di messaggi via seriale anche con 
 * emulatore Android (usato ad esempio per sostituire la comunicazione via 
 * Bluetooth).
 * 
 * 
 * @author acroatti, aricci
 *
 */
public class TestPingPongBTEmu {

	public static void main(String[] args) throws Exception {

		String serialPortName = "/dev/cu.usbmodem14201";
		
		/* setting up the channel, with server for the emu*/
		System.out.print("Creating the serial comm channel with IP server ...");		
		CommChannel channel = new ExtendedSerialCommChannel(serialPortName, 9600, 8080);	
		System.out.println("OK");		
		

		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
		
		/*
		 * Socket used to test when no emu is running 
		 */
		/*
		Socket socket = new Socket("localhost",8080);
		BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));			
		BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		 */
		while (true) {
			/*
			 *  Socket used to test when no emu is running 
			 */
			/*
			System.out.println("Sending ping on BT emu channel...");		
			out.write("ping$\n");
			out.flush();
			
			String msg = in.readLine();
			System.out.println("Received: " + msg);		
			Thread.sleep(500);
			*/
			
			System.out.println("Sending ping on the serial channel...");
			channel.sendMsg("ping");
			String msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
		
		}
	}

}
