#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "config.h"
#include "devices/Pot.h"
#include "devices/Button.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "model/Bridge.h"

class UserConsole {

public:
  UserConsole();

  void init();
  void sync();

  void displayPreAlarm(double waterLevel);
  void displayAlarm(double waterLevel, double valveLevel);
  void turnOffDisplay();
  void turnOnDisplay();

  bool isButtonPressed();
  double getLevel();

  void setManualMode(bool manualMode);
  bool isManualMode();

  void notifyState(bool lightsOn, double waterLevel, int state, bool manual);

  void test();
private:
  Button* pButton; 
  LiquidCrystal_I2C* pLcd; 
  Potentiometer* pPot;
  bool manualMode;
};

#endif
