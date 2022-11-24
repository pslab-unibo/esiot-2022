/*
 * First example on ESP32
 * - IDE to be configured to use the ESP32S3 Dev Module
 *
 */

void setup() {
  Serial.begin(115200);
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());
  delay(2000);
}

void loop() {
  Serial.print("loop() is running on core ");
  Serial.println(xPortGetCoreID());
  delay(1000);
}


