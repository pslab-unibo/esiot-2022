#ifndef __PRINTTASK__
#define __PRINTTASK__

#include "Task.h"

class PrintTask: public Task {

int count;
Task* taskToBeControlled;

public:

  PrintTask(Task* taskToBeControlled);  
  void init(int period);  
  void tick();
};

#endif
