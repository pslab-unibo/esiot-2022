#include <avr/sleep.h>
#include <avr/power.h>
#include "Timer.h"

/* 20191111 - THIS EXAMPLE IS NOT WORKING PROPERLY 
 * the system is not going to enter in power save modality 
 */


Timer* timer;

void setup(){  
  Serial.begin(9600);  
  timer = new Timer();
  timer->setupPeriod(10000);
}

/*
 * Enter sleep mode, with Timer 1 active
 */
void sleep(void)
{
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();

  /* Disable all of the unused peripherals. This will reduce power
   * consumption further and, more importantly, some of these
   * peripherals may generate interrupts that will wake our Arduino from
   * sleep!
   */
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  // power_timer1_disable();
  power_timer2_disable();
  power_twi_disable();  
  /* Now enter sleep mode. */
  sleep_mode();  
  /* The program will continue from here after the timer timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  /* Re-enable the peripherals. */
  power_all_enable();
}

void loop(){
  Serial.println("GOING IN SLEEP MODE IN 1s ...");
  Serial.flush();
  delay(1000);
  sleep();
  Serial.println("WOKE UP " + String(millis()));
}
