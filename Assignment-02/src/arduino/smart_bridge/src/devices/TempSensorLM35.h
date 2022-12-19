#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

#include "TempSensor.h"

class TempSensorLM35: public TempSensor {
public:
  TempSensorLM35(int p);
  virtual float getTemperature();
private:
  int pin;
};


#endif
