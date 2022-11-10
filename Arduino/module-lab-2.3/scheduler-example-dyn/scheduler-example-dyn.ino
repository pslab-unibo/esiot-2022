#include "Scheduler.h"
#include "BlinkTask.h"
#include "PrintTask.h"

Scheduler sched;

void setup(){

  Serial.begin(9600);
  sched.init(100);
 
  Task* t0 = new BlinkTask(13);
  t0->init(100);

  Task* t1 = new PrintTask(t0);
  t1->init(500);
  
  sched.addTask(t0);
  sched.addTask(t1);
   
}

void loop(){
  sched.schedule();
}
