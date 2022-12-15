#include "MsgService.h"

void setup() {
  MsgServiceBT.init();
  MsgService.init();
  
}

void loop() {
  if (MsgServiceBT.isMsgAvailable()) {
    Msg* msg = MsgServiceBT.receiveMsg();    
    if (msg->getContent() == "ping"){
       delay(500);
       MsgServiceBT.sendMsg("pong");
    }
    delete msg;
  }

  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();    
    if (msg->getContent() == "ping"){
       delay(500);
       MsgService.sendMsg("pong");
    }
    delete msg;
  }

}
