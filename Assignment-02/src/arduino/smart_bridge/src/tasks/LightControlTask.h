#ifndef __LIGHT_CONTROL_TASK__
#define __LIGHT_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/Bridge.h"

class LightControlTask: public Task {

public:
  LightControlTask(Bridge* pBridge); 
  void tick();

private:  

  void setState(int state);
  long elapsedTimeInState();

  enum { OFF, ON, GOING_OFF, ALARM} state;
  long stateTimestamp;

  Bridge* pBridge;
};

#endif