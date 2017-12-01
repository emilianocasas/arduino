void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
    digitalWrite(9, HIGH);  
}

void loop() {
  prenderLed();
}

void prenderLed(){
  digitalWrite(9, HIGH);  
}

