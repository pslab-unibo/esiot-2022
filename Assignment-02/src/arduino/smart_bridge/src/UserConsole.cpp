#include "UserConsole.h"
#include "Arduino.h"
#include "devices/ButtonImpl.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "config.h"
#include "kernel/Logger.h"

UserConsole::UserConsole(){
  pLcd = new  LiquidCrystal_I2C(0x27,20,4);
  pButton = new ButtonImpl(BT_PIN);
  pPot = new Potentiometer(POT_PIN);
}

void UserConsole::init(){
  pLcd->init();
  pLcd->backlight();
  pLcd->noDisplay();
  manualMode = false;
}

void UserConsole::sync(){
  pPot->sync();
  pButton->sync();
}

void UserConsole::turnOnDisplay(){
  pLcd->display();
  pLcd->clear();
}

void UserConsole::turnOffDisplay(){
  pLcd->noDisplay();
}

void UserConsole::displayPreAlarm(double waterLevel){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("Pre-Alarm");
  pLcd->setCursor(0, 1); 
  pLcd->print(String("WL:") + waterLevel);
}

void UserConsole::displayAlarm(double waterLevel, double valveLevel){
  pLcd->clear();
  pLcd->setCursor(0, 0); 
  pLcd->print("Alarm");
  pLcd->setCursor(0, 1); 
  pLcd->print(String("WL:") + waterLevel + " VL:" + valveLevel);
}


bool UserConsole::isButtonPressed(){
  return pButton->isPressed();
}

double UserConsole::getLevel(){
  return pPot->getValue();
}

void UserConsole::setManualMode(bool manualMode){
  this->manualMode = manualMode;
}

bool UserConsole::isManualMode(){
  return manualMode;
}

void UserConsole::test(){
    sync();
    if (pButton->isPressed()){
        Logger.log("pressed");
    }
    Logger.log(String("Level: ") + getLevel());
}

void UserConsole::notifyState(bool lightsOn, double waterLevel, int bridgeState, bool manual){
    MsgService.sendMsg(String("br:st:") + (lightsOn ? "1":"0") + ":" + String(waterLevel).substring(0,5) + ":" + bridgeState + ":" + (manual?"1":"0"));  
    // MsgService.sendMsg(String("br:st:") + (lightsOn?"1":"0") + ":" + 0.01 + ":" + "0" + ":" + (manual?"1":"0"));  
}

