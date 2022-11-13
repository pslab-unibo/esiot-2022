#include "async_fsm.h"
#include "buttonImpl.h"
#include "led.h"
#include "console.h"

#define LED_PIN 13
#define BUTTON_PIN 7

class ButtonLedAsyncFSM : public AsyncFSM {
  public:
    ButtonLedAsyncFSM(Button* button, Led* led, Console* console){
      count = 0;  
      currentState = OFF;
      this->button = button;
      this->led = led;
      this->console = console;
      led->switchOff();
      button->registerObserver(this);
    }
  
    void handleEvent(Event* ev) {
      switch (currentState) {
      case OFF:  
        if (ev->getType() == BUTTON_PRESSED_EVENT){
          console->log("ON");
          led->switchOn();
          count = count + 1;
          console->log(count);
          currentState = ON;
        }
        break; 
      case ON: 
        if (ev->getType() == BUTTON_RELEASED_EVENT){
          console->log("OFF");
          led->switchOff();
          count = count + 1;
          console->log(count);
          currentState = OFF;
        }
      }
    }

  private:
    int count; 
    Button* button;
    Led* led;
    Console* console;
    enum  { ON, OFF} currentState;
};

ButtonLedAsyncFSM* myAsyncFSM;

void setup() {
  Button* button = new ButtonImpl(BUTTON_PIN);
  Led* led = new Led(LED_PIN);
  Console* console = new Console();
  myAsyncFSM = new ButtonLedAsyncFSM(button, led, console);
}

void loop() {
  myAsyncFSM->checkEvents();
}
