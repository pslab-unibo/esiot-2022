/*
 * SMART ROOM - Assignment #02 - ESIOT a.y. 2022-2023
 * 
 * Solution sketch by AR
 * 
 */
#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "UserConsole.h"

#include "model/Bridge.h"
#include "tasks/LightControlTask.h"
#include "tasks/WaterControlTask.h"
#include "tasks/UserInputControlTask.h"
#include "tasks/BlinkTask.h"
#include "tasks/ValveControlTask.h"

Scheduler sched;

Bridge* pBridge;
UserConsole* pUserConsole;

void setup() {
  MsgService.init();
  sched.init(50);

  Logger.log(".:: Smart Bridge  ::.");
  
  pBridge = new Bridge();
  pBridge->init();

  pUserConsole = new UserConsole();
  pUserConsole->init();

  Task* pLightControlTask = new LightControlTask(pBridge);
  pLightControlTask->init(100);

  Task* pBlinkTask = new BlinkTask(LEDC_PIN);
  pBlinkTask->init(2000);
  pBlinkTask->setActive(false);

  Task* pValveControlTask = new ValveControlTask(pBridge, pUserConsole);
  pValveControlTask->init(200);

  Task* pUserInputControlTask = new UserInputControlTask(pBridge, pUserConsole);
  pUserInputControlTask->init(50);

  Task* pWaterControlTask = new WaterControlTask(pBridge, pBlinkTask, pValveControlTask);
  pWaterControlTask->init(100);

  sched.addTask(pLightControlTask);
  sched.addTask(pUserInputControlTask);  
  sched.addTask(pWaterControlTask);  
  sched.addTask(pValveControlTask);  
  sched.addTask(pBlinkTask);  
}

void loop() {
    sched.schedule();
    // pUserConsole->test();
}