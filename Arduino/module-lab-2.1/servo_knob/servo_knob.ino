#include "servo_motor_impl.h"
#include "pot.h"

ServoMotor* pMotor;
Pot *pPot;

void setup() {
  Serial.begin(9600);
  pMotor = new ServoMotorImpl(9);
  pPot = new Pot(A0);
  pMotor->on();
}

void loop() {
  int valueInPerc = pPot->getValue();
  Serial.println(valueInPerc);
  int angle = map(valueInPerc, 0, 100, 0, 180);
  pMotor->setPosition(angle); 
  delay(100);
}
