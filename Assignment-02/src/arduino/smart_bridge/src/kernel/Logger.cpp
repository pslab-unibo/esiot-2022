#include "Logger.h"
#include "MsgService.h"

void LoggerService::log(const String& msg){
    MsgService.sendMsg("lo:"+msg);
}



