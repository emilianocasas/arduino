int i=0;

void setup() {
  pinMode(0, INPUT_PULLUP);
    pinMode(15, INPUT_PULLDOWN);
  Serial.begin(9600);

}

void loop() {
  //for (i=0; i<5; i++){
    Serial.write("hola");
  //}

}
