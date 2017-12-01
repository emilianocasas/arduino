volatile boolean contadorDatosFiltro = false;
int cAlarmasAux;
int i = 0;
int o = 0;
int a = 0;
int b = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {

  if (Serial.available()){
      if ((Serial.find("SettearFiltro#")) && (contadorDatosFiltro != true)){
        contadorDatosFiltro = true;
        delay(1000);
        cAlarmasAux = Serial.read() - 48;
        Serial.print("Se crearan ");
        Serial.print(cAlarmasAux);
        Serial.println(" alarmas");
        //inicializarAlarmasAuxiliares(cAlarmasAux);
      }
       
       if (contadorDatosFiltro){
          for (i=0;i<cAlarmasAux; i++){
            Serial.find("("); 
                 delay(1000);
                 o = Serial.read();
                 a = o - 48;
                 Serial.find("-");
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = (a*10) + b;
                 Serial.println(a);
            Serial.find(":"); 
                 delay(1000);
                 o = Serial.read();
                 a = o - 48;
                 Serial.find("-");
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = (a*10) + b;
                 Serial.println(a);     
             Serial.find(","); 
                 delay(1000);
                 o = Serial.read();
                 a = o - 48;
                 Serial.find("-");
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = (a*10) + b;
                 Serial.println(a);         
               Serial.find(":"); 
                 delay(1000);
                 o = Serial.read();
                 a = o - 48;
                 Serial.find("-");
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = (a*10) + b;
                 Serial.println(a);            
              Serial.find(";"); 
                 delay(1000);
                 o = Serial.read();
                 a = o - 48;
                 Serial.println(a);
              }
          contadorDatosFiltro = true;
         }
       }
   }
