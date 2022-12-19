#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"


class LoggerService {
    
public: 
  
  void log(const String& msg);
};

extern LoggerService Logger;

#endif

