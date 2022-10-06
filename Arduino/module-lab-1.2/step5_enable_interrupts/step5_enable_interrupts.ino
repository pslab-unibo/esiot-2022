/**
 * MODIFIED VERSION for SEIOT a.a. 2021-2022 */

// include the EnableInterrupt library - see the links in the related topics section above for details

#define EI_ARDUINO_INTERRUPTED_PIN // to enable pin states functionality 
#include <EnableInterrupt.h>


//DEBUG settings
#define DEBUG 1 // 0 - no debug  


#define ENABLE_INT_IN_PIN 4




volatile uint16_t interruptCountA=0; // The count will go back to 0 after hitting 65535.
volatile uint16_t PinStateSumB=0; // The count will go back to 0 after hitting 65535.

// shared variables are updated by the ISR and read by loop.
// In loop we immediatley take local copies so that the ISR can keep ownership of the
// shared ones. To access these in loop
// we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals
volatile uint8_t InterruptedPinShared;
volatile uint8_t PinStateShared;


void setup()
{ 
  if (DEBUG !=0) {
    Serial.begin(9600);
    Serial.println("setup started ");
  } 

  enableInterrupt(ENABLE_INT_IN_PIN, interruptFunction,CHANGE);
  
  if (DEBUG !=0) {
    Serial.println(" setup completed ");
  }
}

void loop()
{

  static uint8_t InterruptedPin;
  static uint8_t PinState;
  noInterrupts();      // turn interrupts off quickly while we take local copies of the shared variables
   InterruptedPin = InterruptedPinShared;
   PinState = PinStateShared;
   interrupts();  // we have local copies of the inputs, so now we can turn interrupts back on
                  // as soon as interrupts are back on, we can no longer use the  shared variables here

     //Printing
  if (DEBUG !=0) { 
      Serial.print("interruptCountA:");
      Serial.print(interruptCountA);
      Serial.println("");
      Serial.print("PinStateSumB:");
      Serial.print(PinStateSumB);
      Serial.println("");      
      Serial.print("InterruptedPin:");
      Serial.print(InterruptedPin);
      Serial.println("");
      Serial.print("PinState:");
      Serial.print(PinState);
      Serial.println("");
    
     }
     delay(250);

 
}// end of loop


void interruptFunction() {
  //interruptCountA increased each time interrupt called
   interruptCountA++;
  //save values to use them outside the interrupt function  
   InterruptedPinShared=arduinoInterruptedPin;
   PinStateShared=arduinoPinState;
   //PinStateSumB increased each time arduinoPinState=1 detected
   PinStateSumB=PinStateSumB + arduinoPinState ;
 }
