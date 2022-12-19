#ifndef __WATER_CONTROL_TASK__
#define __WATER_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/Bridge.h"
#include "tasks/BlinkTask.h"
#include "tasks/ValveControlTask.h"

class WaterControlTask: public Task {

public:
  WaterControlTask(Bridge* pBridge, BlinkTask* pBlinkTask, ValveControlTask* pValveControlTask); 
  void tick();

private:  

  void setState(int state);
  long elapsedTimeInState();
  bool isTimeToSample();

  enum { NORMAL, PRE_ALARM, ALARM } state;
  long stateTimestamp;

  Bridge* pBridge;
  BlinkTask* pBlinkTask;
  ValveControlTask* pValveControlTask;
};

#endif