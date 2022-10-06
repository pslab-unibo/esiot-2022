#define LED0 3
#define LED1 4
#define LED2 5

unsigned char leds[3]; 

void setup() {  
  leds[0] = LED0;
  leds[1] = LED1;
  leds[2] = LED2;

  for (int i = 0; i < 3; i++){
    pinMode(leds[i], OUTPUT);  
  }
}

int currentLedOn = 0;
int delta = 1;

void loop() {

   digitalWrite(leds[currentLedOn], HIGH);
   delay(200);
   digitalWrite(leds[currentLedOn], LOW);

   if (currentLedOn == 2 || currentLedOn == 0) {
     currentLedOn = 1;
     delta = -delta;
   } else {
     currentLedOn += delta;
   }
   
}
