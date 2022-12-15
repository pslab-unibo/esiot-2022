package esiot.module_lab_3_2;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;

public class TestMQTTClient extends AbstractVerticle {
	
	public static void main(String[] args) throws Exception {		
		Vertx vertx = Vertx.vertx();
		MQTTAgent agent = new MQTTAgent();
		vertx.deployVerticle(agent);
	}
		
}
