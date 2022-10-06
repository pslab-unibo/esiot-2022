/* Main file */

#include "lib.h"


/* global vars */

int count;

void setup() { 
  count = 0;
  if (publicFlag){
    count++;
  }
  Serial.begin(115200);
}

void loop() {
  int myvar = 1; 
  count = myfunc(count);
  Serial.print("hello ");
  Serial.println(count);
  delay(1000);
}
