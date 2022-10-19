#include "LedExt.h"
#include "LightSensorImpl.h"

// the pin must by a PWM one
#define LED_PIN 9

LightExt* led;
LightSensor* lightSensor;

void setup(){
  led = new LedExt(LED_PIN,0);  
  led->switchOn();
  lightSensor = new LightSensorImpl(A0);
  Serial.begin(9600);
}

void loop(){
  int level = lightSensor->getLightIntensity();
  Serial.println(level);  
  if (level < 0){
    level = 0;
  } else if (level > 255){
    level = 255;
  }
  led->setIntensity(255-level);
};
