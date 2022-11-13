#ifndef __CONSOLE__
#define __CONSOLE__

#include "Arduino.h"

class Console {
  public:
    Console();
   void log(const char* msg);
   void log(const String& msg);
   void log(int value);
   void log(float value);
};


#endif
