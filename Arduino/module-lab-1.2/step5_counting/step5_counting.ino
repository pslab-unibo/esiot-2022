#define BUTTON_PIN 2

volatile int count = 0;
int prev = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), inc, RISING); 
}

void loop()
{
  
  noInterrupts();
  int current = count;
  interrupts();
  Serial.println(current);

  /*
  if (current != prev){
    Serial.println(current);
    prev = current;
  }*/
}


void inc()
{
  count++;
}
