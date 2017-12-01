int volatile a = 0;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, funcion, CHANGE);
}

void loop() {

    if (digitalRead(2)) Serial.println("HIGH"); 
   else Serial.println("LOW"); 
    delay(500);
  
 

if (a == 1){
  a = 0;
  Serial.println("Mensaje desde la interrupcion");
}

}

void funcion(){
  a = 1;
}

