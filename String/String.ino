volatile boolean contadorDatosFiltro = false;
int cAlarmasAux;
int i = 0;
int o = 0;
int a = 0;
int b = 0;

volatile int filtroSHRaux[5];
volatile int filtroSMINaux[5];
volatile int filtroEHRaux[5];
volatile int filtroEMINaux[5];
volatile int filtroDaux[5]; 

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()){
      if ((Serial.find("SettearFiltro-")) && (contadorDatosFiltro != true)){
        contadorDatosFiltro = true;
        delay(1000);
        cAlarmasAux = Serial.read() - 48;
        Serial.print("Se crearan ");
        Serial.print(cAlarmasAux);
        Serial.print(" alarmas");
        //inicializarAlarmasAuxiliares(cAlarmasAux);
      }
       
       if (contadorDatosFiltro){
          for (i=0; i<cAlarmasAux; i++){ 
     
               Serial.find("("); 
                 delay(1000);
                 o = Serial.read();
                 a = 0 - 48;
                 Serial.find(o);
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = a + b;
                 meterlo(i,a);
                
              
             Serial.find(":");
                delay(1000); 
                 o = Serial.read();
                 a = 0 - 48;
                 Serial.find(o);
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = a + b;
                 meterlo(i,a);
                 
              
              Serial.find(","); 
                delay(1000);
                 o = Serial.read();
                 a = 0 - 48;
                 Serial.find(o);
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = a + b;
                 meterlo(i,a);
                 
              
              Serial.find(":"); 
                 delay(1000);
                 o = Serial.read();
                 a = 0 - 48;
                 Serial.find(o);
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = a + b;
                 meterlo(i,a);
             
             Serial.find(";");
                 delay(1000); 
                 o = Serial.read();
                 a = 0 - 48;
                 Serial.find(o);
                 delay(1000);
                 b = Serial.read();
                 b = b - 48;
                 a = a + b;
                 meterlo(i,a);
                 
              
             }
           mostrarVectores(cAlarmasAux);
         }
      }
  }


void inicializarAlarmasAuxiliares(int cantAlarmasFiltro){

}

void mostrarVectores(int p){
     Serial.println("Muestro vectores");
     for (int a=0; a<p; a++){
        Serial.println(filtroSHRaux[a]);
        Serial.println(filtroSMINaux[a]);
        Serial.println(filtroEHRaux[a]);
        Serial.println(filtroEMINaux[a]);
        Serial.println(filtroDaux[a]); 
     }
}

void meterlo(int i, int a){
  filtroSHRaux[i] = a;
}

void meterlo1(int i, int a){
 filtroSMINaux[i] = a;
}

void meterlo2(int i, int a){
 filtroEHRaux[i] = a;
}

void meterlo3(int i, int a){
 filtroEMINaux[i] = a;
}

void meterlo4(int i, int a){
 filtroDaux[i] = a;
}



