#define POT_PIN A0
#define LED_PIN 3

int current;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int newValue = analogRead(POT_PIN);
  if (newValue != current){
    current = newValue;
    int intensity = current/4;
    analogWrite(LED_PIN, intensity);
    Serial.println(current);
  }
}
