#include "console.h"
#include "Arduino.h"

Console::Console(){
  Serial.begin(9600);
  while (!Serial) {}
}

void Console::log(const char* msg){
  Serial.println(msg);
}

void Console::log(int value){
  Serial.println(value);
}

void Console::log(float value){
  Serial.println(value);
}

void Console::log(const String& msg){
  Serial.println(msg.c_str());
}
