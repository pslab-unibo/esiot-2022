package esiot.module_lab_3_2;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.mqtt.MqttClient;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle {
	
	public MQTTAgent() {
	}

	@Override
	public void start() {		
		MqttClient client = MqttClient.create(vertx);

		client.connect(1883, "broker.mqtt-dashboard.com", c -> {

			log("connected");
			
			log("subscribing...");
			client.publishHandler(s -> {
			  System.out.println("There are new message in topic: " + s.topicName());
			  System.out.println("Content(as string) of the message: " + s.payload().toString());
			  System.out.println("QoS: " + s.qosLevel());
			})
			.subscribe("esiot-2122", 2);		

			log("publishing a msg");
			client.publish("esiot-2122",
				  Buffer.buffer("hello"),
				  MqttQoS.AT_LEAST_ONCE,
				  false,
				  false);
		});
	}
	

	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}

}