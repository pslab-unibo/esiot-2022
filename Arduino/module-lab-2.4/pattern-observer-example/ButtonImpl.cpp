#include "ButtonImpl.h"
#include "Arduino.h"

#define DEBOUNCING_TIME 30

/* ----------------------- ButtonImpl --------------- */

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);  
  nListeners = 0;  
  lastEventTime = millis();
  bindInterrupt(pin);
} 
  
bool ButtonImpl::isPressed(){
  return digitalRead(pin) == HIGH;
}

/*
 * Called by the interrupt dispatcher, signaling a new interrupt
 * on the specific pin
 */
void ButtonImpl::notifyInterrupt(int pin){
  long curr = millis();
  if (curr - lastEventTime > DEBOUNCING_TIME){
    lastEventTime = curr;
    if (isPressed()){
      for (int i = 0; i < nListeners; i++){
        listeners[i]->notifyButtonPressed();
      }  
    } else {
      for (int i = 0; i < nListeners; i++){
        listeners[i]->notifyButtonReleased();
      }  
    }
  }
}
