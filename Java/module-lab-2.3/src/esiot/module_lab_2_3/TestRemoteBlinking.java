package esiot.module_lab_2_3;

/**
 * Testing simple message passing.
 * 
 * To be used with an Arduino connected via Serial Port
 * running module-lab-2.3/remote_blinking/remote_blinking.ino
 * 
 * @author aricci
 *
 */
public class TestRemoteBlinking {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel(args[0],9600);		
		// SerialCommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			channel.sendMsg("1");
			String msg = channel.receiveMsg();
			System.out.println(msg);		
			Thread.sleep(500);
		
			channel.sendMsg("0");
			msg = channel.receiveMsg();
			System.out.println(msg);
			Thread.sleep(500);

		}
	}

}
