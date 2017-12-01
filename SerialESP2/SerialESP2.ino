char c;
int i = 0;
int nbuf = 0;
char comando[256];
boolean lock = false;
int contador = 0;
int contador2 = 3;
boolean finDeCadena = false;
boolean flag = false;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
    if (Serial.available()){
    
          if (contador == 0){
              contador = 1;
              nbuf = 0;
              lock = true;
              finDeCadena = true;
           }
          c = Serial.read();
          Serial.print(c);
          Serial.println(nbuf);
            if (c != ')') {
                comando[nbuf] = c;
               nbuf++;
            }else {
             Serial.println("    ....fin de cadena");
              lock = false;
            }
          if (flag) {
            flag = false;
            nbuf = 0;
            finDeCadena = false;
            contador = 0;
            lock = false;
          }

     }
  

if (lock == 0){
  if (finDeCadena){
    finDeCadena = false;
    flag = true;
    Serial.print("Muestro cadena --->"); Serial.println(comando);
    parseoCadena();
    Serial.println(nbuf);
    contador = 0;
    Serial.print("Muestro cadena denuevo --->"); Serial.println(comando);
  }
 }
}

 
void parseoCadena(){
  switch(comando[0]){
    case 'A': 
         Serial.println("Alarma");             
         break;
    case 'R': 
         Serial.println("Rodrigo");             
         break;
    default:
         Serial.println("Ninguno de los dos");             
         break;
  }
}







