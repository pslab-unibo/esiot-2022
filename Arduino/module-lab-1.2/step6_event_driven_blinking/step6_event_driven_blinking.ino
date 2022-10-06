#include "TimerOne.h"

#define LED_PIN 3

boolean flagState = false;

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
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(blinky); 
  Serial.begin(9600);
}

void loop(){
  Serial.println(flagState);
}
