#ifndef __BRIDGE__
#define __BRIDGE__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/LightSensor.h"

class Bridge {
    
public: 
    Bridge();
    void init();
    
    double getCurrentWaterLevel();
    double getCurrentLightLevel();
    double getCurrentValveLevel();

    bool isLightOn();
    bool detectedPresence();

    void turnLightOn();
    void turnLightOff();

    bool isNormalState();
    bool isPreAlarmState();
    bool isAlarmState();
    
    /* */
    
    void setNormalState();
    void setPreAlarmState();
    void setAlarmState();

    void samplePresence();
    void sampleWaterLevel();
    void sampleLightLevel();
    void setValveLevel(double level);

    void test();

private:

    double waterLevel;
    double lightLevel;
    double valveLevel;
    bool lightState;
    bool detectedPres;
    
    enum { NORMAL, PRE_ALARM, ALARM} state;

    Led* pLightSystem;
    Sonar* pSonar;
    Pir* pPir;
    LightSensor* pLightSensor;

    Led* pBridgeAccessibleLight;
    Led* pBridgeAlarmLight;
};


#endif