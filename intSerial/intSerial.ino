void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial2.begin(9600);
  attachInterrupt(0, funcionInt, FALLING);
}

void loop() {
  

}

void funcionInt(){
  if (Serial2.available()) Serial.println("Mensaje recibido");
}

