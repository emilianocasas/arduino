int a = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Esto se ve");
  delay(1000);
  if (a=1) return;
  Serial.println("Esto no se ve");
  delay(1000);
}
