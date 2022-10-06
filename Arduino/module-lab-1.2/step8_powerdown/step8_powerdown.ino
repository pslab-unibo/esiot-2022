#include <avr/sleep.h>

void wakeUp(){}

void setup(){  
  Serial.begin(9600);  
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING); 
}

void loop(){
  Serial.println("GOING IN POWER DOWN IN 1s ...");
  Serial.flush();
  delay(1000);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  /** The program will continue from here. **/  
  Serial.println("WAKE UP");
  /* First thing to do is disable sleep. */  
  sleep_disable();   
}
