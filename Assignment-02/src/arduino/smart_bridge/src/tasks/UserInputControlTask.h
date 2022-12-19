#ifndef __USER_INPUT_CONTROL_TASK__
#define __USER_INPUT_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/Bridge.h"
#include "UserConsole.h"

class UserInputControlTask: public Task {

public:

  UserInputControlTask(Bridge* pBridge, UserConsole* pUserConsole); 
  void tick();

private:  

  void setState(int state);
  long elapsedTimeInState();

  enum { IDLE, PRE_ALARM, ALARM_AUTO_MODE, ALARM_MANUAL_MODE} state;
  long stateTimestamp;

  bool wasPressed;
  Bridge* pBridge;
  UserConsole* pUserConsole;
};

#endif