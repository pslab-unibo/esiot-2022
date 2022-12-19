#ifndef __BUTTON__
#define __BUTTON__

class Button {
 
public:
  Button();
  virtual bool isPressed() = 0;
  virtual bool isClicked() = 0;

  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
