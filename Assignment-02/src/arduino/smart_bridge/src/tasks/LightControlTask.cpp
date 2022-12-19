#include "tasks/LightControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

#define DELAY_BEFORE_OFF 1000

LightControlTask::LightControlTask(Bridge* pBridge): 
    pBridge(pBridge) {
    setState(OFF);
}
  
void LightControlTask::tick(){
    pBridge->samplePresence();
    pBridge->sampleLightLevel();

    switch (state){    
    case OFF: {
        if (pBridge->isAlarmState()){
            Logger.log("LC:from OFF to ALARM");
            setState(ALARM);
        } else if (pBridge->detectedPresence() && pBridge->getCurrentLightLevel() < 0.5){
            Logger.log("LC:from OFF to ON");
            pBridge->turnLightOn();
            setState(ON);
        }
        break;
    }
    case ON: {        
        // Logger.log("LC:state ON");
        if (pBridge->isAlarmState()){
            pBridge->turnLightOff();
            Logger.log("LC:from ON to ALARM");
            setState(ALARM);
        } else if (!pBridge->detectedPresence() || pBridge->getCurrentLightLevel() > 0.8){
            Logger.log("LC:from ON to GOING OFF");
            setState(GOING_OFF);
        }
        break;       
    }

    case GOING_OFF: {
        if (pBridge->isAlarmState()){
            Logger.log("LC:from GOING OFF to ALARM");
            pBridge->turnLightOff();
            setState(ALARM);
        } else if (pBridge->detectedPresence() && pBridge->getCurrentLightLevel() < 0.5){
            Logger.log("LC:from GOING OFF to ON");
            setState(ON);
        } else if (this->elapsedTimeInState() > DELAY_BEFORE_OFF){
            Logger.log("LC:from GOING OFF to OFF");
            pBridge->turnLightOff();
            setState(OFF);
        }
        break;
    }

    case ALARM: {
        // Logger.log("LC:state ALARM");
        if (!pBridge->isAlarmState()){
            Logger.log("LC:from ALARM to OFF");
            setState(OFF);
        }
        break;
    }}
}

void LightControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long LightControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

