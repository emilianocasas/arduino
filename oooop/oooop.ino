void setup() {
  pinMode(2, OUTPUT);
Serial.begin(9600);
}

void loop() {
  Serial.println("Prendo");
  digitalWrite(2, HIGH);
  delay(1500);
  Serial.println("Apago");
  digitalWrite(2, LOW);
  delay(1500);
}
