boolean pv_flag = true;
char comando[256];
int nbuf = 0;
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {

    while (Serial2.available()){
     if (pv_flag){
      pv_flag = false;
      i = 0;
      Serial.println("Aparezco una vez");
     }
    if (Serial.read() == ')'){
      pv_flag = true;
      i = 0;
    }
        agregarCaracter(Serial2.read());
      }
    
    

    
    if (Serial.available()){
      int valor = Serial.read();
      if (valor == 48) Serial.println(nbuf);
      if (valor == 49) mostrarComando();
      if (valor == 50) mostrarComando3();
    }
}

void agregarCaracter (char c){
  comando[nbuf] = c;
  if (c != ')') nbuf++;
}

void mostrarComando(){
  int a;
  for (a=0; a<nbuf; a++) Serial.write(comando[a]);
}

void mostrarComando3(){
   Serial.write(comando[2]);
}


