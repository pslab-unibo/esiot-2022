#include "MsgServiceBT.h"
#include "SoftwareSerial.h"

/*
 *  BT module connection:  
 *  - RX is pin 2 => to be connected to TXD of BT module
 *  - TX is pin 3 => to be connected to RXD of BT module
 *
 */ 
MsgServiceBT msgService(2,3);

void setup() {
  msgService.init();  
  Serial.begin(9600);
  while (!Serial){}
  Serial.println("ready to go."); 
}

void loop() {
  if (msgService.isMsgAvailable()) {
    Msg* msg = msgService.receiveMsg();
    Serial.println(msg->getContent());    
    if (msg->getContent() == "ping"){
       msgService.sendMsg(Msg("pong"));
       delay(500);
    }
    delete msg;
  }
}
