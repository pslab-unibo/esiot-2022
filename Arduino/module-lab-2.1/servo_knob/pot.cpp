#include "pot.h"

#include "Arduino.h"

Pot::Pot(int p): pin(p) {   
}

int Pot::getValue(){
  int val = analogRead(pin);
  return map(val, 0, 1023, 0, 100);
}
