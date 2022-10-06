#define POT_PIN A0

int current;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int newValue = analogRead(POT_PIN);
  if (newValue != current){
    current = newValue;
    Serial.println(current);
  }
}
