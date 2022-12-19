package esiot.smart_bridge;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.LayoutManager;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.LinkedList;

import javax.swing.*;

class SmartBridgeView extends JFrame implements ActionListener  {

	// private JButton refill, recover;
	private JTextField lightsState;
	private JTextField bridgeState;
	private JTextField lastWaterLevel;
	private JTextField valveManMode;
	private Controller controller;	
	private GraphicPanel graphicPanel;
	
	public SmartBridgeView(){
		super(".:: Smart Bridge ::.");
		setSize(600,600);

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel infoLine = new JPanel();
		infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));
		bridgeState = new JTextField("--");
		bridgeState.setEditable(false);
		bridgeState.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Bridge State:"));
		infoLine.add(bridgeState);
		lightsState = new JTextField("--");
		lightsState.setEditable(false);
		lightsState.setPreferredSize(new Dimension(100,15));
		infoLine.add(new JLabel("Light State:"));
		infoLine.add(lightsState);
		lastWaterLevel = new JTextField("--");
		lastWaterLevel.setEditable(false);
		lastWaterLevel.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Water Level:"));
		infoLine.add(lastWaterLevel);
		
		mainPanel.add(infoLine);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));	    
		/*
		refill = new JButton("Refill");
		refill.setEnabled(false);
		buttonPanel.add(refill);
		recover = new JButton("Recover");
		recover.setEnabled(false);
		buttonPanel.add(recover);
		refill.addActionListener(this);
		recover.addActionListener(this);
		*/
		mainPanel.add(buttonPanel);

		graphicPanel = new GraphicPanel(300,300);
		// mainPanel.add(graphicPanel);
		
		
		JPanel cp = new JPanel();
		LayoutManager layout = new BorderLayout();
		cp.setLayout(layout);
		cp.add(BorderLayout.NORTH,mainPanel);
		cp.add(BorderLayout.CENTER,graphicPanel);
		// cp.add(BorderLayout.SOUTH, infoPanel);
		setContentPane(cp);	
		
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
	}

	public void registerController(Controller contr){
		this.controller = contr;
	}

	public void setBridgeState(String msg){
		SwingUtilities.invokeLater(() -> {
			if (msg.equals("0")) {
				bridgeState.setText("Normal");
			} else if (msg.equals("1")) {
				bridgeState.setText("Pre-Alarm");
			} else if (msg.equals("2")) {
				bridgeState.setText("Alarm");
			} 
		});
	}

	public void setLightsState(boolean msg){
		SwingUtilities.invokeLater(() -> {
			lightsState.setText(msg ? "on":"off");
		});
	}
	
	public void setWaterLevel(double waterLevel){
		SwingUtilities.invokeLater(() -> {
			lastWaterLevel.setText(""+waterLevel);
		});
	}
	
	public void updateSamples(Sample[] samples) {
		try {
			SwingUtilities.invokeAndWait(() -> {
				graphicPanel.updateSamples(samples);
			});
		} catch (Exception ex) {}
	}
	/*
	public void startMaintenanceForRefilling() {
		SwingUtilities.invokeLater(() -> {
			refill.setEnabled(true);
		});
	}

	public void startMaintenanceForRecovering() {
		SwingUtilities.invokeLater(() -> {
			recover.setEnabled(true);
		});
	}
	*/
	
	public void actionPerformed(ActionEvent ev){
		/*
		  try {
			  if (ev.getActionCommand().equals("Refill")){
				  controller.notifyRefilled();
				  refill.setEnabled(false);
			  } else {
				  controller.notifyRecovered();
				  recover.setEnabled(false);
			  }
		  } catch (Exception ex){
			  ex.printStackTrace();

		  }
		  */
	  }
	
	   public static class GraphicPanel extends JPanel {
	        	    	
	        private long dx;
	        private long dy;
	        private Sample[] samples;
	        
	        public GraphicPanel(int w, int h){
	            setSize(w,h);
				setFocusable(true);
				setFocusTraversalKeysEnabled(false);
				requestFocusInWindow(); 
	        }

	        public void paint(Graphics g){    		    		
	    		if (samples != null) {
	        		Graphics2D g2 = (Graphics2D) g;
	        		
	        		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	        		          RenderingHints.VALUE_ANTIALIAS_ON);
	        		g2.setRenderingHint(RenderingHints.KEY_RENDERING,
	        		          RenderingHints.VALUE_RENDER_QUALITY);
	        		g2.clearRect(0,0,this.getWidth(),this.getHeight());

	        		if (samples.length > 0) {
	        			Sample s = samples[0];
	        			long t0 = s.getTimestamp();
	        			double wl = s.getValue();
	        			
	        			int x0 = 20;
	        			int y0 = 400;
	        			int dw = 400;
	        			int dh = 300;
	        			int ds = 4000;
	        			double dwl = 3;

	        			// System.out.println("NEW SAMPLES: ");
	        			for (int i = 1; i < samples.length; i++) {
	        				Sample s2 = samples[i];
		        			long t2 = s2.getTimestamp();
		        			double wl2 = s2.getValue();
	        				
		        			int x2 = x0 + (int)((t2 - t0)*dw/ds);
		        			int y2 = y0 - (int)(wl2*dh/dwl);
		        			// System.out.print("("+t2+","+wl2+")=>("+x2+","+y2+"),");
		        			g2.drawOval(x2, y2, 2, 2);
	        			}	
	        			
	        			
	        		}
	        		
		    		// String time = String.format("%.2f", vt);
		    		// g2.drawString("Bodies: " + bodies.size() + " - vt: " + time + " - nIter: " + nIter + " (UP for zoom in, DOWN for zoom out)", 2, 20);
	    		}
	        }
	        
	        public void updateSamples(Sample[] samples) {
	        	this.samples = samples;
	        	this.repaint();
	        }
	        
	        
	 }
}
