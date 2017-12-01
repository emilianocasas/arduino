boolean volatile f = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  attachInterrupt(0, funcion, FALLING);
}

void loop() {
   if (f){
    f = false;
    Serial.println("infsdfsdfdst");
    digitalWrite(5, HIGH);
    delay(2000);
    digitalWrite(5, LOW);
   }

}

void funcion(){
  f = true;
}

