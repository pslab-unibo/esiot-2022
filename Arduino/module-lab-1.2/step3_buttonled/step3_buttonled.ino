#define BUTTON_PIN 2  
#define LED_PIN 13  

void setup() {
  pinMode(LED_PIN, OUTPUT);      
  pinMode(BUTTON_PIN, INPUT);     
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {     
    digitalWrite(LED_PIN, HIGH);  
    Serial.println("Pressed");
  } else {
    digitalWrite(LED_PIN, LOW); 
  }
  delay(1000);
}
