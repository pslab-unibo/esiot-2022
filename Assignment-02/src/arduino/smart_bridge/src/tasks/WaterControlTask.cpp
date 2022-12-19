#include "tasks/WaterControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "UserConsole.h"

#define SAMPLING_PERIOD_NORMAL 1000
#define SAMPLING_PERIOD_PRE_ALARM 500
#define SAMPLING_PERIOD_ALARM 250


WaterControlTask::WaterControlTask(Bridge* pBridge, BlinkTask* pBlinkTask, ValveControlTask* pValveControlTask): 
    pBridge(pBridge), pBlinkTask(pBlinkTask), pValveControlTask(pValveControlTask) {
    setState(NORMAL);
    pBridge->setNormalState();
}
  
void WaterControlTask::tick(){
    pBridge->sampleWaterLevel();

    switch (state){    
    case NORMAL: {
        if (elapsedTimeInState() > SAMPLING_PERIOD_NORMAL){
            pBridge->sampleWaterLevel();
            if (pBridge->getCurrentWaterLevel() > WL1){
                Logger.log("WC:switch to PRE-ALARM");
                pBridge->setPreAlarmState();
                pBlinkTask->setActive(true);
                setState(PRE_ALARM);
            }
        }
        break;
    }
    case PRE_ALARM: {        
        if (elapsedTimeInState() > SAMPLING_PERIOD_PRE_ALARM){
            pBridge->sampleWaterLevel();
            if (pBridge->getCurrentWaterLevel() > WL2){
                Logger.log("WC:switch to ALARM");
                pBridge->setAlarmState();
                pBlinkTask->setActive(false);
                setState(ALARM);
            } else if (pBridge->getCurrentWaterLevel() <= WL1){
                Logger.log("WC:back to NORMAL");
                pBlinkTask->setActive(false);
                pBridge->setNormalState();
                setState(NORMAL);
            } 
        }
        break;       
    }

    case ALARM: {
        if (elapsedTimeInState() > SAMPLING_PERIOD_ALARM){
            pBridge->sampleWaterLevel();
            if (pBridge->getCurrentWaterLevel() <= WL2){
                Logger.log("WC:back to PRE-ALARM");
                pBridge->setPreAlarmState();
                pBlinkTask->setActive(true);
                setState(PRE_ALARM);
            }
        }
        break;
    }
    }
}

void WaterControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long WaterControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool WaterControlTask::isTimeToSample(){

}
  