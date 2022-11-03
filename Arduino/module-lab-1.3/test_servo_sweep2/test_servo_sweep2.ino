#include "servo_motor_impl.h"

int pos;   
int delta;
ServoMotor* pMotor;

void setup() {
  Serial.begin(9600);
  pMotor = new ServoMotorImpl(3);
  pos = 0;
  delta = 1;
}

void loop() {
  pMotor->on();
  for (int i = 0; i < 180; i++) {
    Serial.println(pos);
    pMotor->setPosition(pos);         
    // delay(15);            
    pos += delta;
  }
  pMotor->off();
  pos -= delta;
  delta = -delta;
  delay(1000);
}
