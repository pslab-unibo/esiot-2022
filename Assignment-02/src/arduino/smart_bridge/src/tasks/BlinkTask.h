#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "kernel/Task.h"
#include "devices/Led.h"

class BlinkTask: public Task {

  int pin;
  Light* led;
  enum { ON, OFF} state;

public:

  BlinkTask(int pin);  
  void init(int period);  
  void tick();
};

#endif

