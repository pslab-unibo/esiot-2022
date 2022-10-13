#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A2);
  
  /* value : 1023 = value_in_mV : 5000 */
  /* value_in_mV = 5000/1023 * value */
  
  int value_in_mV = 4.8876 * value; 

  /* value_in_C = value_in_mV / 10 (since we have 10 mV => 1 °C ) */

  double value_in_C = value_in_mV * 0.1;
  
  Serial.println(value_in_C);

  
  
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  lcd.print(String("Value in C: ") + value_in_C);

  delay(1000);
}
