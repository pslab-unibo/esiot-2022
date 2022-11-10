#include "Arduino.h"
#include "config.h"

#define NLEDS 4

uint8_t ledPin[] = {LED01_PIN, LED02_PIN, LED03_PIN, LED04_PIN};
uint8_t pulseIntensity = 0;
uint8_t pulseDelta = 5;

extern void log(const String& msg);

void init_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(LED_START, OUTPUT);     
}

void reset_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], LOW);     
  }
}

void test_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], HIGH);     
    delay(500);
    digitalWrite(ledPin[i], LOW);     
  }
  for (int i = 0; i < 10; i++){
    analogWrite(LED_START, i*25);     
    delay(100);
  }
  for (int i = 9; i >= 0; i--){
    analogWrite(LED_START, i*25);     
    delay(100);
  }
}

void reset_pulsing() {
  pulseIntensity = 0;
  pulseDelta = 5;
  analogWrite(LED_START, pulseIntensity);   
}

void go_on_pulsing(){
  analogWrite(LED_START, pulseIntensity);   
  pulseIntensity = pulseIntensity + pulseDelta;
  if (pulseIntensity == 0 || pulseIntensity == 255) {
    pulseDelta = -pulseDelta ; 
  }     
  delay(15);                               
}

void turn_on_pattern(unsigned char pattern){
  unsigned char mask = 0x01;
  for (int i = 0; i < NLEDS; i++){
    if ((pattern & mask) != 0){
      digitalWrite(ledPin[i], HIGH);     
    } 
    mask <<= 1;
  }
}

void turn_off_pattern(){
  reset_led_board();
}
