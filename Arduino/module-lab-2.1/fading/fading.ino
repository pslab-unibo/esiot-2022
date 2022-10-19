#include "LedExt.h"

// the pin must by a PWM one
#define LED_PIN 6

LightExt* led;
int brightness;
int fadeAmount;

void setup(){
  brightness = 0;
  fadeAmount = 5;
  led = new LedExt(LED_PIN,brightness);  
  led->switchOn();
}

void loop(){
  led->setIntensity(brightness);
  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  delay(20);   
   
};
