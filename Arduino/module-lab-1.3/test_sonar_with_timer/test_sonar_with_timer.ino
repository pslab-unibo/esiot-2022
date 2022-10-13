#include "Timer.h"

const int trigPin = 8;
const int echoPin = 7;

/* supponendo di eseguire il test 
   in un ambiente a 20 °C 
   https://it.wikipedia.org/wiki/Velocità_del_suono
   */ 
const double vs = 331.45 + 0.62*20;

Timer* timer;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  timer = new Timer();
  timer->setupPeriod(200);
}

float getDistance()
{
    /* invio impulso */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* ricevi l’eco */
    long tUS = pulseInLong(echoPin, HIGH);
    Serial.println(tUS);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
}


void loop()
{
  timer->waitForNextTick();
  float d = getDistance();
  Serial.println(d);
}
