#include "lib.h"
#include <arduino.h>

/* public */
int publicFlag;

/* private */
static int privateVar;

int myfunc(int x) {
  delay(1000);
  return x + 1;
}
