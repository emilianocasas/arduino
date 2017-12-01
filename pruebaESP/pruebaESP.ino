
void setup(){

Serial.begin(9600);
}

void loop(){
 //if (Serial.available()){
  //int valor = Serial.read();
  Serial.println("Soy el esp");
  delay(10);
 //}
}
