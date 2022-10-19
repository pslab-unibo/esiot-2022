/*
 * Implementation of the class Counter
 *
 */
#include "counter.h"

Counter::Counter(int value){
  count = value;
}

void Counter::inc(){
  count++;  
}

int Counter::getValue(){
  return count;
}


