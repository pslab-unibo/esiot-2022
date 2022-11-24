/*
 * Second example, about tasks that can be run
 * thanks to FreeRTOS support.  
 *
 */
 
TaskHandle_t Task1;
TaskHandle_t Task2;

const int led_1 = 4;
const int led_2 = 5;

void setup() {
  Serial.begin(115200); 
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);                         
  delay(500); 

  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);          
    delay(500); 
}

void Task1code( void * parameter ){
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_1, HIGH);
    delay(500);
    digitalWrite(led_1, LOW);
    delay(500);
  } 
}

void Task2code( void * parameter ){
  Serial.print("Task2 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_2, HIGH);
    delay(1000);
    digitalWrite(led_2, LOW);
    delay(1000);
  }
}

void loop() {
  Serial.print("this is the main loop running on core ");
  Serial.println(xPortGetCoreID());
  delay(1000000);
}
