#include "PrintTask.h"
#include "Arduino.h"

PrintTask::PrintTask(Task* task){
  taskToBeControlled = task;
}
  
void PrintTask::init(int period){
  Task::init(period);
  count = 0;
}
  
void PrintTask::tick(){
  count++;
  Serial.println("> " + String(count) + " " + String(millis()));
  
  if (count % 5 == 0){
    if (taskToBeControlled->isActive()){
      taskToBeControlled->setActive(false);
      Serial.println("de-activating...");
    } else {
      taskToBeControlled->setActive(true);
      Serial.println("activating...");
    }
  }
}
