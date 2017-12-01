char *comando;

void setup() {
  Serial.begin(9600);
  comando[0] = 'a';
}

void loop() {
  
  Serial.println(comando[0]);
  }

