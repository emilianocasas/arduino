const int LED_Blanco = 13;
const int LED_Verde = 12;
int Byte_entrada = 0;

void setup() {
  Serial.begin(9600); //Abre el puerto serie
  pinMode(LED_Blanco, OUTPUT);
  pinMode(LED_Verde, OUTPUT);
  digitalWrite(LED_Blanco, LOW);
  digitalWrite(LED_Verde, LOW);
}

void loop() {
  if (Serial.available()>0){ //¿Puerto serie disponible?
    Byte_entrada = Serial.read();//Leemos lo que transmitimos desde Java
    if (Byte_entrada =='0'){
      digitalWrite(LED_Blanco, LOW);
    } else if (Byte_entrada =='1') {
      digitalWrite(LED_Blanco, HIGH);
    } else if (Byte_entrada =='2') {
      digitalWrite(LED_Verde, LOW);
    } else if (Byte_entrada =='3') {
      digitalWrite(LED_Verde, HIGH);
    }
  }
}
