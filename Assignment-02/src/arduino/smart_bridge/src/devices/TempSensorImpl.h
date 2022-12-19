#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

class TempSensorLM35: public TempSensor {

public:
  TempSensorLM35(int pin);	
  virtual float getTemperature();
  
private:
  int pin;
};


#endif

