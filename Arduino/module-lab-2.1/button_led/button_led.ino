#include "Led.h"
#include "ButtonImpl.h"

#define LED_PIN    13
#define BUTTON_PIN 2
 
Light* led;
Button* button;

void setup(){
  led = new Led(LED_PIN);  
  button = new ButtonImpl(BUTTON_PIN);
}

void loop(){
  if (button->isPressed()){
    led->switchOn();
  } else {
    led->switchOff();
  }
};
