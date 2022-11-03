#include "Led.h"
#include "Timer.h"
#include "ButtonImpl.h"

#define LED_PIN 13
#define BUTTON_PIN 2 

Light* led;
Button* button;
Timer timer;

enum { ON, OFF} state;

void setup(){
  Serial.begin(9600);
  led = new Led(LED_PIN); 
  button = new ButtonImpl(BUTTON_PIN);
  state = OFF;
  timer.setupPeriod(50);
}

void step(){
  bool isPressed;  
  switch (state){
    case OFF:
      isPressed = button->isPressed();      
      if (isPressed){
        led->switchOn();
        Serial.println("ON");
        state = ON;
      }
      break;
    case ON:
      isPressed = button->isPressed();      
      if (!isPressed){
        led->switchOff();
        Serial.println("OFF");
        state = OFF;
      }
      break;
  }
}

void loop(){
  timer.waitForNextTick();
  step();
};
