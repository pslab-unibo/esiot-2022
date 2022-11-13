#ifndef __BUTTON__
#define __BUTTON__

#include "async_fsm.h"

#define BUTTON_PRESSED_EVENT 1
#define BUTTON_RELEASED_EVENT 2

class Button : public EventSource {
public: 
  virtual bool isPressed() = 0;
};

class ButtonPressed: public Event {
public:
  ButtonPressed(Button* source) : Event(BUTTON_PRESSED_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};

class ButtonReleased: public Event {
public:
  ButtonReleased(Button* source) : Event(BUTTON_RELEASED_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};

#endif
