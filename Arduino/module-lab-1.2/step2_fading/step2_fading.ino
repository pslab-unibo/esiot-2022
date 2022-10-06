// deve essere un pin che supporta PWM
#define LED_PIN 10

int brightness;
int fadeAmount;
int currIntensity;

void setup(){
  currIntensity = 0;
  fadeAmount = 5;
  pinMode(LED_PIN, OUTPUT);     
}

void loop(){
  analogWrite(LED_PIN, currIntensity);   
  currIntensity = currIntensity + fadeAmount;
  if (currIntensity == 0 || currIntensity == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  delay(15);                               
}
