#include "ThreeLedsTask.h"
#include "Arduino.h"

ThreeLedsTask::ThreeLedsTask(int pin0, int pin1, int pin2){
  this->pin[0] = pin0;    
  this->pin[1] = pin1;    
  this->pin[2] = pin2;    
}
  
void ThreeLedsTask::init(int period){
  Task::init(period);
  for (int i = 0; i < 3; i++){
    led[i] = new Led(pin[i]); 
  }
  state = 0;    
}
  
void ThreeLedsTask::tick(){
  led[state]->switchOff();
  state = (state + 1) % 3;
  led[state]->switchOn();
  delayMicroseconds(10000);
}
