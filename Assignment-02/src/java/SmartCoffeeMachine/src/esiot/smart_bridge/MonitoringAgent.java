package esiot.smart_bridge;

import java.util.LinkedList;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	SmartBridgeView view;
	LogView logger;
	
	static final String BRIDGE_PREFIX 	=  "br:";
	static final String LOG_PREFIX 	=  "lo:";
	static final String MSG_STATE 		= "st:";
	/*
	static final String MSG_SLEEPING 		= "zz";
	static final String MSG_READY 			= "ok";
	static final String MSG_MAKING 			= "ma";
	static final String MSG_ASSISTANCE  	= "as";
	static final String MSG_NUM_ITEMS  		= "ni";
	static final String MSG_NUM_SELF_TESTS	= "nt";
	*/
	
	LinkedList<Sample> samples;
	
	public MonitoringAgent(SerialCommChannel channel, SmartBridgeView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}
	
	public void run(){
		samples = new LinkedList<Sample>();
		while (true){
			try {
				String msg = channel.receiveMsg();
				if (msg.startsWith(BRIDGE_PREFIX)){
					String cmd = msg.substring(BRIDGE_PREFIX.length()); 
					// logger.log("new command: "+cmd);				
					
					if (cmd.startsWith(MSG_STATE)){
						try {
							String args = msg.substring(MSG_STATE.length()); 
	
							String[] elems = args.split(":");
							boolean lightsOn = elems[1].equals("1");
							double waterLevel = Double.parseDouble(elems[2]);
							String bridgeState = elems[3];
							boolean manual = elems[4].equals("1");
	
							Sample s = new Sample(System.currentTimeMillis(), waterLevel);
							samples.addLast(s);
							
							if (samples.size() > 100) {
								samples.removeFirst();
							}
							// String("st") + lightsOn + ":" + waterLevel + ":" + alarm + ":" + manual);  
	
							view.setLightsState(lightsOn);
							view.setWaterLevel(waterLevel);
							view.setBridgeState(bridgeState);
							var arraySamples = new Sample[samples.size()];
							samples.toArray(arraySamples);
							view.updateSamples(arraySamples);
						} catch (Exception ex) {
							System.err.println("Error in msg: " + cmd);
						}
					}
					/* else if (cmd.startsWith(MSG_SLEEPING)){
						view.setState("Sleeping");
					} else if (cmd.startsWith(MSG_READY)){
						view.setState("Ready");
					} else if (cmd.startsWith(MSG_MAKING)) {
						view.setState("Making a product");
					} else if (cmd.startsWith(MSG_ASSISTANCE)) {
						view.setState("Assistance");
						String reason = cmd.substring(3);
						if (reason.equals("ni")) {
							view.startMaintenanceForRefilling();
						} else {
							view.startMaintenanceForRecovering();
						}
					} else if (cmd.startsWith(MSG_NUM_ITEMS)) {
						view.setNumItems(cmd.substring(3));
					} else if (cmd.startsWith(MSG_NUM_SELF_TESTS)) {
						view.setNumSelfTests(cmd.substring(3));
					}
					*/
				} else if (msg.startsWith(LOG_PREFIX)){
					this.logger.log(msg.substring(LOG_PREFIX.length()));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
