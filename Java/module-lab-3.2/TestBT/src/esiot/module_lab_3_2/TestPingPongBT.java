package esiot.module_lab_3_2;

import esiot.module_lab_2_2.SerialCommChannel;

public class TestPingPongBT {

	public static void main(String[] args) throws Exception {

		String BT_PORT_NAME = "/dev/cu.isi00"; /* OS dependent */
		
		//SerialCommChannel channel = new SerialCommChannel(args[0],9600);		
		
		SerialCommChannel channel = new SerialCommChannel(BT_PORT_NAME,9600);		

		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			System.out.println("Sending ping");
			channel.sendMsg("ping");
			String msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
		}
	}

}
