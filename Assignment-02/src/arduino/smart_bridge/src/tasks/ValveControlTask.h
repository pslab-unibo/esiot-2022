#ifndef __VALVE_CONTROL_TASK__
#define __VALVE_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/Bridge.h"
#include "devices/servo_motor.h"
#include "UserConsole.h"

class ValveControlTask: public Task {

public:
  ValveControlTask(Bridge* pBridge, UserConsole* pUserConsole); 
  void tick();

private:  

  void setState(int state);
  long elapsedTimeInState();

  enum { CLOSED, OPEN, CLOSING} state;
  long stateTimestamp;

  Bridge* pBridge;
  ServoMotor* pMotor;  
  UserConsole* pUserConsole;
};

#endif