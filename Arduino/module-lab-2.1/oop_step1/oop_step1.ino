#include "counter.h"

Counter c(10);
Counter* c1;

void setup(){
  Serial.begin(9600); 
  c1 = new Counter(20);
}

void loop(){
  int x = 0;
  
  c.inc();
  Serial.println(c.getValue());
  c1->inc();
  Serial.println(c1->getValue());
  delay(10);

  
  Counter* c3 = new Counter(micros());
  Serial.println(c3->getValue());
  delete c3;

  Counter c2(10);
  c2.inc();
    
}
