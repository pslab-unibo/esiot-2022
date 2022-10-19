#include "Led.h"

#define LED_PIN 13

class FakeLed: public Light { 
public:
  FakeLed(){
    Serial.begin(9600);
  }
  
  void switchOn() {
     Serial.println("switchon");
  }
  void switchOff(){
     Serial.println("switchoff");
  }
};



Light* led;

void setup(){
  led = new Led(LED_PIN);  
  // led = new FakeLed();  
}

void loop(){
  led->switchOn();
  delay(500);
  led->switchOff(); 
  delay(500);
};
