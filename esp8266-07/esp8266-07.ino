void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}

void loop() {

      
      //Serial.println("Hola");
      if (Serial.available()) digitalWrite(13, HIGH);      
      
    }
 
    


