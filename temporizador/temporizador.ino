void setup() {
  pinMode(7, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(7) == 0) Serial.println("7 en LOW");
}
