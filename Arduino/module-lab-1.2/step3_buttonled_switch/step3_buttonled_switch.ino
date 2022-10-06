/*
 * Button functioning as a switch
 * pressed => switch the light
 */
#define BUTTON_PIN 2  
#define LED_PIN 13   

boolean ledState;
boolean buttonStatePressed;


void setup() {
  pinMode(LED_PIN, OUTPUT);      
  pinMode(BUTTON_PIN, INPUT);     
  ledState = false;
  buttonStatePressed = false;
  digitalWrite(LED_PIN,LOW);
  Serial.begin(9600);
}

void loop() {
  int buttonPressed = digitalRead(BUTTON_PIN);
  // debouncing
  delay(20);
  
  if (!buttonStatePressed) {
    if (buttonPressed){
      buttonStatePressed = true;
      if (ledState){
        digitalWrite(LED_PIN, LOW);  
        ledState = false;
        Serial.println("Switched off.");
      } else {
        digitalWrite(LED_PIN, HIGH);  
        ledState = true;
        Serial.println("Switched on.");
      }
    }
  } else {
    if (!buttonPressed){
      buttonStatePressed = false;         
    }
  }
}
