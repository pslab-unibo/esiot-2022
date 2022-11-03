#include "Led.h"
#include "Timer.h"

#define LED_PIN 13

Light* led;
Timer timer;

enum { ON, OFF} state;

void setup(){
  Serial.begin(9600);
  led = new Led(LED_PIN); 
  state = OFF;
  timer.setupPeriod(100);
}

void step(){
  switch (state){
    case OFF:
      led->switchOn();
      Serial.println("ON");
      state = ON;
      break;
    case ON:
      led->switchOff();
      Serial.println("OFF");
      state = OFF;
      break;
  }
}

void loop(){
  timer.waitForNextTick();
  step();
};
