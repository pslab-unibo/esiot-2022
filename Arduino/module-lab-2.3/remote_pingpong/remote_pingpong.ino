#include "MsgService.h"

void setup() {
  MsgService.init();
  
}

void loop() {
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();    
    if (msg->getContent() == "ping"){
       delay(500);
       MsgService.sendMsg("pong");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
  }
}
