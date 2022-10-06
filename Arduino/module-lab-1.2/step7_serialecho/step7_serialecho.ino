void setup()
{
  Serial.begin(115200); 
}

void loop()
{
  if (Serial.available()){
    char data = Serial.read();
    Serial.print(data);
  }  
}
