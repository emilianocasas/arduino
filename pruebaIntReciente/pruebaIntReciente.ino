
int volatile a = 0;


void funcion(){
a = 1;
}


void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    attachInterrupt(0, funcion, RISING);
}

void loop() {

   //Serial.println(digitalRead(2));
  if (a == 1){
    Serial.println("Entre en la interrupcion");
  }

}

