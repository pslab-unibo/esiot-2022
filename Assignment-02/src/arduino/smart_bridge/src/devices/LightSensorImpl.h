#include "LightSensor.h"

class LightSensorImpl: public LightSensor {

public: 
  LightSensorImpl(int pin);
  double getLightIntensity();
  
private:
  int pin;
};
