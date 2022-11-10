#include "Scheduler.h"
#include "BlinkTask.h"
#include "ThreeLedsTask.h"

Scheduler sched;

void setup(){
  
  sched.init(50);
  
  Task* t0 = new BlinkTask(13);
  t0->init(500);
  sched.addTask(t0);

  Task* t1 = new ThreeLedsTask(7,8,9);
  t1->init(150);
  sched.addTask(t1);  
    
}

void loop(){
  sched.schedule();
}
