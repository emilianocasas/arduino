
void pin2Interrupt(void){
  delay(100);
  Serial.println("Estoy en la interrupcion");
}

void setup(){
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(2, INPUT);
  attachInterrupt(0, pin2Interrupt, FALLING);
  
  Serial.println("Initialisation complete.");
  pinMode(12, HIGH);
}

void loop()
{
   if (Serial.available()){
    int v = Serial.read();
    if (v == 48){
       digitalWrite(12, LOW); 
    }
    if (v == 49){
       digitalWrite(12, HIGH); 
    }
}
}

