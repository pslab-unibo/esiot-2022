package esiot.module_lab_3_2;

import io.vertx.core.*;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;

public class VertxHTTPServerExample extends AbstractVerticle {
	@Override
	public void start() throws Exception {
		// Create a Router
		Router router = Router.router(vertx);

		// Mount the handler for all incoming requests at every path and HTTP method
		router.route().handler(context -> {
			// Get the address of the request
			String address = context.request().connection().remoteAddress().toString();
			// Get the query parameter "name"
			MultiMap queryParams = context.queryParams();
			String name = queryParams.contains("name") ? queryParams.get("name") : "unknown";
			// Write a json response
			context.json(new JsonObject().put("name", name).put("address", address).put("message",
					"Hello " + name + " connected from " + address));
		});

		// Create the HTTP server
		vertx.createHttpServer()
				// Handle every request using the router
				.requestHandler(router)
				// Start listening
				.listen(8080)
				// Print the port
				.onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()));
	}

	public static void main(String[] args) {
		Vertx vertx = Vertx.vertx();
		VertxHTTPServerExample service = new VertxHTTPServerExample();
		vertx.deployVerticle(service);

	}

}