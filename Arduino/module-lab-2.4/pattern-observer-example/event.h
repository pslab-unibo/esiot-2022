#ifndef __EVENT__
#define __EVENT__

#define NUM_PINS 13

/**
 * Base class representing an event source
 */
class EventSource {
  public:
    /* called by the interrupt dispatcher to notify a new event */
    virtual void notifyInterrupt(int pin) = 0;

  protected:
    void bindInterrupt(int pin);
}; 

/**
 * Class binding interrupts to event sources
 */
class InterruptDispatcher {
  public:
    InterruptDispatcher();        

    /* to bind an event source to a specific pin */
    void bind(int pin, EventSource* src);

    /* called by interrupt handlers */
    void notifyInterrupt(int pin);
  private:
    EventSource* sourceRegisteredOnPin[NUM_PINS];
    void (*notifyFunctions[NUM_PINS])() = {};

    static void notifyInterrupt_0();
    static void notifyInterrupt_1();
    static void notifyInterrupt_2();
    static void notifyInterrupt_3();
    static void notifyInterrupt_4();
    static void notifyInterrupt_5();
    static void notifyInterrupt_6();
    static void notifyInterrupt_7();
    static void notifyInterrupt_8();
    static void notifyInterrupt_9();
    static void notifyInterrupt_10();
    static void notifyInterrupt_11();
    static void notifyInterrupt_12();
    static void notifyInterrupt_13();
    

};

#endif
