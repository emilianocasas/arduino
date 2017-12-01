int sensorValue = 0;
float voltage = 0;

void setup() {
  pinMode(1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
     sensorValue = analogRead(A0);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.println("----------------------------");
       Serial.print("A0(3.3V)    :  "); Serial.println(voltage);
       Serial.println(" ");
       sensorValue = analogRead(A1);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("A1(5V)    :  "); Serial.println(voltage);
       Serial.println(" ");
           sensorValue = analogRead(A2);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("MA2(5V)    :  "); Serial.println(voltage);
       Serial.println(" ");
                  sensorValue = analogRead(A3);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("MA2(3.3V)    :  "); Serial.println(voltage);
       Serial.println("----------------------------");
       digitalWrite(1, HIGH);
        Serial.println("----------------------------");
       Serial.print("A0(3.3V)    :  "); Serial.println(voltage);
       Serial.println(" ");
       sensorValue = analogRead(A1);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("A1(5V)    :  "); Serial.println(voltage);
       Serial.println(" ");
           sensorValue = analogRead(A2);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("MA2(5V)    :  "); Serial.println(voltage);
       Serial.println(" ");
                  sensorValue = analogRead(A3);
        voltage = sensorValue * (5.0 / 1023.0);
       Serial.print("MA2(3.3V)    :  "); Serial.println(voltage);
       Serial.println("----------------------------");
       digitalWrite(1, LOW);
    }
  }

}
