package esiot.smart_bridge;

import javax.swing.SwingUtilities;

class SmartBridgeConsole   {

	static SmartBridgeView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/
		SwingUtilities.invokeAndWait(() -> {
			view = new SmartBridgeView();
			log = new LogView();
		});
		String portName = "/dev/cu.usbmodem1432401";
		Controller contr = new Controller(portName,view,log);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			log.setVisible(true);
		});
	}
}