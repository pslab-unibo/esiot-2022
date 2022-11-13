 #ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"

class ButtonImpl: public Button {
 
public: 
  ButtonImpl(int pin);
  virtual bool isPressed();
  virtual void notifyInterrupt(int pin);
  
private:
  int pin;
  long lastEventTime;
};

#endif
