#ifndef __TIMER__
#define __TIMER__

class Timer {
    
public:  
  Timer();
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();

};


#endif

