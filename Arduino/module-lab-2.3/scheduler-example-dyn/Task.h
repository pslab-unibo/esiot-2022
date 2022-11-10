#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;
  bool active;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    active = true;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool isActive(){
    return active;
  }

  void setActive(bool active){
    this->active = active;
  }
  
};

#endif
