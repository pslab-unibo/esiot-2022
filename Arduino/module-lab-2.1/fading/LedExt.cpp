#include "LedExt.h"
#include "Arduino.h"

LedExt::LedExt(int pin) : Led(pin) {
  currentIntensity = 128;
  isOn = false;
}

LedExt::LedExt(int pin, int intensity) : Led(pin) {
  isOn = false;
  currentIntensity = intensity;
}

void LedExt::switchOn(){
  analogWrite(pin,currentIntensity);
  isOn = true;
}

void LedExt::setIntensity(int value){
 currentIntensity = value;  
 if (isOn){
   analogWrite(pin,currentIntensity);   
 }
}

void LedExt::switchOff(){
  analogWrite(pin,0);
  isOn = false;
}
