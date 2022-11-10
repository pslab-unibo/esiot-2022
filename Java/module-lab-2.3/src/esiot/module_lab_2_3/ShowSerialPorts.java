package esiot.module_lab_2_3;

import java.io.IOException;

import jssc.*;

public class ShowSerialPorts {

	public static void main(String[] args) {
		
		/* detect serial ports */
		String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}

	}

}
