package esiot.module_lab_3_2;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;

public class TestClient extends AbstractVerticle {
	
	public static void main(String[] args) throws Exception {		
	
		String host = "localhost"; // "b1164b27.ngrok.io";
		int port = 8080;

		Vertx vertx = Vertx.vertx();
		
		JsonObject item = new JsonObject();
		item.put("value", 20 + Math.random()*5);
		item.put("place","nowhere");

		WebClient client = WebClient.create(vertx);

		System.out.println("Posting new data item... ");
		client
		.post(port, host, "/api/data")
		.sendJson(item)
		.onSuccess(response -> {
			System.out.println("Posting - Received response with status code: " + response.statusCode());
		});
		
		Thread.sleep(1000);
		
		System.out.println("Getting data items... ");
		client
		  .get(port, host, "/api/data")
		  .send()
		  .onSuccess(res -> { 
			  System.out.println("Getting - Received response with status code: " + res.statusCode());
			  JsonArray response = res.bodyAsJsonArray();
		      System.out.println(response.encodePrettily());
		  })
		  .onFailure(err ->
		    System.out.println("Something went wrong " + err.getMessage()));
	}
	
}
