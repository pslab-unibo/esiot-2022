#include "servo_motor_impl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;  
} 

void ServoMotorImpl::on(){
  motor.attach(pin);    
}

void ServoMotorImpl::setPosition(int angle){
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  float coeff = (2250.0-750.0)/180;
  motor.write(750 + angle*coeff);              
}

void ServoMotorImpl::off(){
  motor.detach();    
}
