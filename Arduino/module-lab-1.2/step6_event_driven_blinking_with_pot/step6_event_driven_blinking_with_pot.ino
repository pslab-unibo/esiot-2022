#include "TimerOne.h"

#define LED_PIN 3
#define POT_PIN A0

boolean flagState = false;
unsigned long period;

void blinky(){
  if (!flagState){
    digitalWrite(LED_PIN, HIGH);  
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
  flagState = !flagState;
}


void setup()
{
  pinMode(LED_PIN,OUTPUT);
  /* set period timer 1000000 usec = 1 sec */
  Timer1.initialize(); 
  period = 1000000l;
  Timer1.attachInterrupt(blinky, period); 
  Serial.begin(9600);
}

void loop(){
  // Serial.println(flagState);
  int val = analogRead(POT_PIN);
  unsigned long newPeriod = 1000l * val;
  if (newPeriod == 0) {
    newPeriod = 100;
  }
  if (newPeriod != period){
    period = newPeriod;
    Timer1.setPeriod(period);
    Serial.println(period);
  }
}
