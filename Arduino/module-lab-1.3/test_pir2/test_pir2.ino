#define PIR_PIN 2
#define CALIBRATION_TIME_SEC 10

bool detectedStatus;

void setup(){
  pinMode(PIR_PIN,INPUT);
  Serial.begin(9600);
  
  //give the sensor some time to calibrate
  Serial.print("Calibrating sensor... ");
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");
  detectedStatus = false;
  delay(50);
}

void loop(){
  int current = digitalRead(PIR_PIN);
  if (current != detectedStatus ){
    detectedStatus = current;
    if (current) {
      Serial.println("detected!");  
    } else {
      Serial.println("no more detected.");
    }
  }
};
