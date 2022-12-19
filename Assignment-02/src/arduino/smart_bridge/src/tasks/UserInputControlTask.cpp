#include "tasks/UserInputControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "UserConsole.h"

#define NORMAL_STATE 0
#define PRE_ALARM_STATE 1
#define ALARM_STATE 2 

UserInputControlTask::UserInputControlTask(Bridge* pBridge, UserConsole* pUserConsole): 
    pBridge(pBridge), pUserConsole(pUserConsole) {
    setState(IDLE);
    pUserConsole->turnOffDisplay();
}
  
void UserInputControlTask::tick(){

    switch (state){    
    case IDLE: {
        // Logger.log("UI:state NORMAL");
        pUserConsole->notifyState(pBridge->isLightOn(), pBridge->getCurrentWaterLevel(), NORMAL_STATE, false);
        if (pBridge->isPreAlarmState()){
            pUserConsole->turnOnDisplay();
            Logger.log("UI:going to PRE_ALARM");
            setState(PRE_ALARM);
        }
        break;
    }
    case PRE_ALARM: {        
        // Logger.log("UI:state PRE");
        pUserConsole->displayPreAlarm(pBridge->getCurrentWaterLevel());
        pUserConsole->notifyState(pBridge->isLightOn(), pBridge->getCurrentWaterLevel(), PRE_ALARM_STATE, false);
        if (pBridge->isAlarmState()){
            wasPressed = false;
            setState(ALARM_AUTO_MODE);
        } else if (pBridge->isNormalState()){
            pUserConsole->turnOffDisplay();
            Logger.log("UI:back to IDLE");
            setState(IDLE);
        } 
        break;       
    }

    case ALARM_AUTO_MODE: {
        pUserConsole->displayAlarm(pBridge->getCurrentWaterLevel(), pBridge->getCurrentValveLevel());
        pUserConsole->sync();
        pUserConsole->notifyState(pBridge->isLightOn(), pBridge->getCurrentWaterLevel(), ALARM_STATE, false);
        if (pBridge->isPreAlarmState()){
            setState(PRE_ALARM);
        } else if (pUserConsole->isButtonPressed()){
            if (!wasPressed) {
                wasPressed = true;
            }
        } else if (wasPressed) {
            wasPressed = false;
            pUserConsole->setManualMode(true);
            Logger.log("UI:ALARM - switch to MANUAL");
            setState(ALARM_MANUAL_MODE);
        }
        break;
    }

    case ALARM_MANUAL_MODE: {
        pUserConsole->displayAlarm(pBridge->getCurrentWaterLevel(), pBridge->getCurrentValveLevel());
        pUserConsole->sync();
        pUserConsole->notifyState(pBridge->isLightOn(), pBridge->getCurrentWaterLevel(), ALARM_STATE, true);
        if (pBridge->isPreAlarmState()){
            setState(PRE_ALARM);
        } else if (pUserConsole->isButtonPressed()){
            if (!wasPressed) {
                wasPressed = true;
            }
        } else if (wasPressed) {
            wasPressed = false;
            pUserConsole->setManualMode(false);
            Logger.log("UI:ALARM - switch to AUTO");
            setState(ALARM_AUTO_MODE);
        }
        break;
    }}
}

void UserInputControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long UserInputControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

