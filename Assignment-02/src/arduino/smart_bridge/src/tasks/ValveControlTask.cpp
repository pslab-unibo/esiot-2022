#include "tasks/ValveControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "devices/servo_motor_impl.h"

ValveControlTask::ValveControlTask(Bridge* pBridge, UserConsole* pUserConsole): pUserConsole(pUserConsole),  
    pBridge(pBridge) {
    pMotor = new ServoMotorImpl(VALVE_PIN);
    setState(CLOSED);
}
  
void ValveControlTask::tick(){
    switch (state){    
    case CLOSED: {
        if (pBridge->isAlarmState()){
            pMotor->on();
            setState(OPEN);
        }
        break;
    }
    case OPEN: {        
        if (!pBridge->isAlarmState()){
            pMotor->setPosition(0);
            setState(CLOSING);
        } else {
            if (pUserConsole->isManualMode()){
                double valveLevelToBeSet = pUserConsole->getLevel(); /* from 0 to 1 */
                pBridge->setValveLevel(valveLevelToBeSet);
            } else {
                double wl = pBridge->getCurrentWaterLevel();
                double valveLevelToBeSet = (wl-WL2)/(MAX_WL-WL2); /* from 0 to 1 */
                pBridge->setValveLevel(valveLevelToBeSet);
            }
            int angle = pBridge->getCurrentValveLevel()*180;
            pMotor->setPosition(angle);
            Logger.log(String("VT: valve ") + pBridge->getCurrentValveLevel() + " motor " + angle);
        }
        break;       
    }

    case CLOSING: {
        if (pBridge->isAlarmState()){
            setState(OPEN);
        } else if (elapsedTimeInState() > 1000){
            pMotor->off();
            setState(CLOSED);
        }
        break;
    }
    }
}

void ValveControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long ValveControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

