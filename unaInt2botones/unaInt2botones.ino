void setup() {
  pinMode(2, INPUT);
   pinMode(5, INPUT);
    pinMode(6, INPUT);
Serial.begin(9600);


}


void loop() {
 if (Serial.available()) {
    int val = Serial.read();
   
    if (val == 49) {
      if (digitalRead(2)) Serial.println("El 2 esta en HIGH");
      else Serial.println("El 2 esta en LOW");
      
      if (digitalRead(5)) Serial.println("El 5 esta en HIGH");
      else Serial.println("El 5 esta en LOW");
      
      if (digitalRead(6)) Serial.println("El 6 esta en HIGH");
      else Serial.println("El 6 esta en LOW");
      }
}


}
