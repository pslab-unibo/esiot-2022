#define PHOTORES_PIN A0
#define FREQ 5
#define PERIOD 1000/FREQ

void setup(){
  pinMode(PHOTORES_PIN, INPUT);
  Serial.begin(9600);
}

void loop(){
  int value = analogRead(PHOTORES_PIN);
  Serial.println(value);
  delay(PERIOD);
};
