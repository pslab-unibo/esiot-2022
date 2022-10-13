#include "Timer.h"

#define PHOTORES_PIN A0
#define FREQ 10
#define PERIOD 1000/FREQ

Timer* timer;

void setup(){
  pinMode(PHOTORES_PIN, INPUT);
  Serial.begin(9600);
  timer = new Timer();
  timer->setupPeriod(PERIOD);
}

void loop(){
  timer->waitForNextTick();
  int value = analogRead(PHOTORES_PIN);
  Serial.println(value);
};
