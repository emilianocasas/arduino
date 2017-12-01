volatile boolean a = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, funcion, FALLING);
}

void loop() {
  Serial.println("Empiezan los delays");
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);
  //  if (a){
    //  a = false;
     // Serial.println("int1");
   // }
}

void funcion(){
  //a = true;
  Serial.println("int");
}

