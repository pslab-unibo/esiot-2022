#ifndef __COUNTER_H__
#define __COUNTER_H__
/*
 * Declaration of the class Counter
 *
 */
class Counter {
  int count;  

public:

  Counter(int value);
  void inc();
  int getValue();
};

#endif
