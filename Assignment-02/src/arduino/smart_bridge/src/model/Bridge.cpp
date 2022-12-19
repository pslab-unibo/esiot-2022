#include "model/Bridge.h"
#include "config.h"
#include "devices/Led.h"
#include "kernel/Logger.h"
#include "devices/LightSensorImpl.h"

#define MAX_DISTANCE_FROM_RIVER 3.00

Bridge::Bridge(){
}

void Bridge::init(){
    pLightSystem = new Led(LEDA_PIN);
    pSonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
    pPir = new Pir(PIR_PIN);
    pLightSensor =  new LightSensorImpl(LIGHT_SENSOR_PIN);
    pBridgeAccessibleLight = new Led(LEDB_PIN);
    pBridgeAlarmLight = new Led(LEDC_PIN);

    detectedPres = false; 
    valveLevel = 0;
    setNormalState();
}

void Bridge::samplePresence(){
    this->pPir->sync();
    this->detectedPres = pPir->isDetected();
}

void Bridge::sampleWaterLevel(){   
    /*
     * mapping: 
     * 0 - 0.01 m => 3.0 (max) - 2.0 m 
     * 0.01 - 0.02 m => 2.0 - 1.0 m   
     * > 0.02 => < 1.0 m
    */ 
    double d = pSonar->getDistance();
    if (d == NO_OBJ_DETECTED){
        this->waterLevel = 0;
    } else {
        double dist = MAX_DISTANCE_FROM_RIVER - d*10;
        if (dist < 0){
            dist = 0;
        }
        this->waterLevel = dist;
    }
}

void Bridge::sampleLightLevel(){   
    this->lightLevel = pLightSensor->getLightIntensity();
}

double Bridge::getCurrentWaterLevel(){
    return waterLevel;
}

double Bridge::getCurrentLightLevel(){
    return lightLevel;
}

bool Bridge::isLightOn(){
    return lightState;
}

bool Bridge::isNormalState(){
    return state == NORMAL;
}

bool Bridge::isPreAlarmState(){
    return state == PRE_ALARM;
}

bool Bridge::isAlarmState(){
    return state == ALARM;
}

void Bridge::setAlarmState() {
    state = ALARM;
    pBridgeAccessibleLight->switchOff();
    pBridgeAlarmLight->switchOn();
}

void Bridge::setNormalState() {
    state = NORMAL;
    pBridgeAccessibleLight->switchOn();
    pBridgeAlarmLight->switchOff();
}

void Bridge::setPreAlarmState() {
    state = PRE_ALARM;
    pBridgeAccessibleLight->switchOn();
    pBridgeAlarmLight->switchOff();
}

void Bridge::turnLightOn(){
    pLightSystem->switchOn();
    lightState = true;
}

void Bridge::turnLightOff(){
    pLightSystem->switchOff();
    lightState = false;
}

bool Bridge::detectedPresence(){
    return this->detectedPres; 
}

double Bridge::getCurrentValveLevel(){
    return valveLevel;
}

void Bridge::setValveLevel(double level){
    this->valveLevel = level;
}


void Bridge::test(){
}
