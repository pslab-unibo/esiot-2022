#include <LiquidCrystal_I2C.h> 

/* Wiring: SDA => A4, SCL => A5 */
/* I2C address of the LCD: 0x27 */
/* Number of columns: 20 rows: 4 */
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  lcd.print("Hello World!");
}
