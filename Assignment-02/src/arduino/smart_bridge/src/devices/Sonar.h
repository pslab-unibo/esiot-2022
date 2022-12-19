#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"

#define NO_OBJ_DETECTED -1

class Sonar: public ProximitySensor {

public:  
  Sonar(int echoPin, int trigPin, long maxTime);
  float getDistance();
  void setTemperature(float temp);  

private:
    const float vs = 331.5 + 0.6*20;
    float getSoundSpeed();
    
    float temperature;    
    int echoPin, trigPin;
    long timeOut;
};

#endif 
