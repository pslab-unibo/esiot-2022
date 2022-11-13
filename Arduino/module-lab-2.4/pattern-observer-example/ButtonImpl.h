#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"

class ButtonImpl: public AbstractButton { 
public: 
  ButtonImpl(int pin);
  bool isPressed();
  
protected:
  void notifyInterrupt(int pin);

private:
  int pin;
  /* for debouncing */
  int lastEventTime;
};

#endif
