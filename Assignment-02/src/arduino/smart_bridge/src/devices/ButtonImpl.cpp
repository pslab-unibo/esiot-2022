#include "ButtonImpl.h"
#include "Arduino.h"

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);  
  sync();   
} 
  
bool ButtonImpl::isPressed(){
  return pressed;
}

bool ButtonImpl::isClicked(){
  return clicked;
}

void ButtonImpl::sync(){
  bool wasPressed = pressed;
  pressed = digitalRead(pin) == HIGH;
  if (!pressed){
    if (wasPressed){
      clicked = true;
    } else {
      if (clicked){
        clicked = false;
      }
    }
  } else if (pressed){
    clicked = false;
  }
  updateSyncTime(millis());
}
