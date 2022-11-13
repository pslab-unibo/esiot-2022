/*
 * Pattern observer example.
 */
#include "ButtonImpl.h"
 
class MyListener : public ButtonListener {
public:
  MyListener(){
    count = 0;  
  }

  void notifyButtonPressed(){
    count++;
  }

  void notifyButtonReleased(){
    count++;
  }

  int getCount(){
    noInterrupts();
    int c = count;
    interrupts();
    return c;  
  }  
private:
  volatile int count;
};

AbstractButton* buttonA, *buttonB;
MyListener* listener;

void setup(){
  Serial.begin(9600);
  buttonA = new ButtonImpl(4);
  buttonB = new ButtonImpl(5);
  listener = new MyListener();
  buttonA->addListener(listener);
  buttonB->addListener(listener);
}

void loop(){
  Serial.println(listener->getCount());
};
