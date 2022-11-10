package esiot.module_lab_2_3;

/**
 *
 */
public class SimpleSerialMonitor  {

	public static void main(String[] args) throws Exception {
		if (args.length != 1){
			System.out.println("args: <CommPortName>");
			System.exit(1);
		} else {
			String comPortName = args[0];
			System.out.println("Start monitoring serial port "+args[0]+" at 9600 boud rate");
			try {
				SerialMonitor monitor = new SerialMonitor();
				monitor.start(comPortName);							
				Thread.sleep(1000000);
			} catch (InterruptedException ex) {
				ex.printStackTrace();
			}
		}
	}
}