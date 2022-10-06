#define LED0 3
#define LED1 4
#define LED2 5

unsigned char leds[3]; 

#define STATE_LED0_ON 0
#define STATE_LED1_ON_FWD 1
#define STATE_LED1_ON_REV 2
#define STATE_LED2_ON 3

void setup() {  
  leds[0] = LED0;
  leds[1] = LED1;
  leds[2] = LED2;

  for (int i = 0; i < 3; i++){
    pinMode(leds[i], OUTPUT);  
  }
}

int currentState = STATE_LED0_ON;

void loop() {

   if (currentState == STATE_LED0_ON){
      digitalWrite(leds[0], HIGH);
      delay(200);
      digitalWrite(leds[0], LOW);
      currentState = STATE_LED1_ON_FWD;
   } else if (currentState == STATE_LED1_ON_FWD){
      digitalWrite(leds[1], HIGH);
      delay(200);
      digitalWrite(leds[1], LOW);
      currentState = STATE_LED2_ON;
   } else if (currentState == STATE_LED2_ON){
      digitalWrite(leds[2], HIGH);
      delay(200);
      digitalWrite(leds[2], LOW);
      currentState = STATE_LED1_ON_REV;
   } else if (currentState == STATE_LED1_ON_REV){
      digitalWrite(leds[1], HIGH);
      delay(200);
      digitalWrite(leds[1], LOW);
      currentState = STATE_LED0_ON;
   }
}
