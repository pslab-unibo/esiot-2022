#ifndef __POT_H__
#define __POT_H__

class Pot {

public:
  
  Pot(int pin);
   
  /**
   * return a value in percentage
   */
  int getValue();  

private:
  int pin;

};

#endif
