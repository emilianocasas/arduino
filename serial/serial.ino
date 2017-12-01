volatile int cAlarmasAux = 0;
volatile int a = 0;
volatile char *buf = (char *) malloc(8);

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);
}

void loop() {
  if (Serial1.available()){
     if ((Serial1.find("SettearFiltro-")) ){
       a =0; 
        while (a!=9){
        delay(100);
        buf[a] = Serial1.read();
        a++;
      }
     mostrarComando(8);
  }
 }
}
 
void mostrarComando(int n){
  int i = 0;
  for (i=0; i<n; i++){
    Serial.print(buf[i]);  
  }
}








