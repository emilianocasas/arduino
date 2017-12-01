#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 

#define pinBomba 10

DS3231 clock;
RTCDateTime dt;

volatile boolean settearProxAlarma_flag = false;
volatile int contador;
volatile int contadorAux;
volatile int rangoI;
volatile int cantAlarmas;
//volatile int cantAlarmasDia[7];
volatile int operacion;
//volatile char* alarmaFlag;
//volatile int* alarmaStartHR;
//volatile int* alarmaStartM;
//volatile int* alarmaEndHR;
//volatile int* alarmaEndM;
//volatile int* alarmaDay;

volatile int Hour;
volatile int i;
volatile int Minute;

//tmElements_t tm;

void setup() {
   volatile int alarmaStartHR[7];
   volatile int alarmaStartM[7];
   volatile int alarmaEndHR[7];
   volatile int alarmaEndM[7];
   volatile int *alarmaDay[7];
   volatile int cantAlarmasDia[7];
   volatile char alarmaFlag[7];

  alarmaStartHR[0] = 10; 
  alarmaStartHR[1] = 10;
  alarmaStartHR[2] = 13;
  alarmaStartHR[3] = 14;
  alarmaStartHR[4] = 15;
  alarmaStartHR[5] = 20;
  alarmaStartHR[6] = 21;
  alarmaStartM[0] = 0;
  alarmaStartM[1] = 30;
  alarmaStartM[2] = 0;
  alarmaStartM[3] = 0;
  alarmaStartM[4] = 45;
  alarmaStartM[5] = 0;
  alarmaStartM[6] = 0;
  alarmaEndHR[0] = 11;
  alarmaEndHR[1] = 12;
  alarmaEndHR[2] = 13;
  alarmaEndHR[3] = 15;
  alarmaEndHR[4] = 15;
  alarmaEndHR[5] = 20;
  alarmaEndHR[6] = 22;
  alarmaEndM[0] = 0;
  alarmaEndM[1] = 45;
  alarmaEndM[2] = 5;
  alarmaEndM[3] = 40;
  alarmaEndM[4] = 50;
  alarmaEndM[5] = 45;
  alarmaEndM[6] = 0;
  alarmaDay[0]= 5;
  alarmaDay[1]= 4;
  alarmaDay[2]= 0;
  alarmaDay[3]= 5;
  alarmaDay[4]= 0;
  alarmaDay[5]= 4;
  alarmaDay[6]= 3;
  alarmaFlag[0]= 'F';
  alarmaFlag[1]= 'F';
  alarmaFlag[2]= 'L';
  alarmaFlag[3]= 'F';
  alarmaFlag[4]= 'P';
  alarmaFlag[5]= 'F';
  alarmaFlag[6]= 'F';
  cantAlarmasDia[0]= 2;
  cantAlarmasDia[1]= 2;
  cantAlarmasDia[2]= 3;
  cantAlarmasDia[3]= 4;
  cantAlarmasDia[4]= 4;
  cantAlarmasDia[5]= 2;
  cantAlarmasDia[6]= 2;

  cantAlarmas = 7;
  rangoI = 8;

  
  Serial.begin(9600);
  setSyncProvider(RTC.get);  
  RTC.squareWave(SQWAVE_NONE);
  clock.setDateTime(2015,7,15, 13, 2, 0);

 // leerHora();
  Hour = 11;
  Minute = 0;
 // chequeoProxAlarma();
 // if (settearProxAlarma_flag ) settearProxAlarma();
 // else obtenerRango();
 obtenerRango(alarmaDay);
  Serial.println("Termine obtener rango");
}

void loop() {


 if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48){
       mostrarEstadoAlarmas();
       //Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));
        Serial.print("Hora --> ");
        Serial.println(Hour);
        Serial.print("Minutos --> ");
        Serial.println(Minute);
       
  }
 }


//if (RTC.alarm(ALARM_1)) {
  //   funcionAlarma();
  //}      
}

void leerHora(){
//  RTC.read(tm);
}


void obtenerRango(int *vec){
 // Serial.println("obtengo rango");
 // Serial.println(Hour);
 // Serial.println(Minute);
  //int i = 0;
  //boolean aux_flag = true;
  
             for (i=0; i<7; i++ ){
               // if (rangoI == cantAlarmas + 1){
                   // if (alarmaDay[i] == 0 ){ //Si la alarma debe ser ejecutada en el dia actual
                  //  Serial.print("Entre en el for con i= ");
                  //  Serial.println(i);
                    Serial.print(i+1);
                    Serial.print("   ");
                    Serial.println(vec[i+1]);
                        //if (alarmaStartHR[i] <= Hour <= alarmaEndHR[i]){  //Si la hora actual es igual a la de la start o end de la alarma..
                          //   if (alarmaStartHR[i] == Hour){
                            //      if (alarmaStartM[i] <= Minute){
                              //        rangoI = i;
                                //      Serial.print("Cambio rangoI con i=");
                                  //    Serial.println(i);
                                     
                                   //} else {
                                   // aux_flag = false;
                                    
                                   //}
                              //}
                              //if (alarmaEndHR[i] == Hour){
                                //  if (alarmaEndM[i] >= Minute){
                                 // rangoI = i;
                                 // Serial.print("Cambio rangoI con i=");
                                 // Serial.println(i);
                                  
                                  //} else {
                                   // aux_flag = false;
                                    
                              //    }
                             // }
                              //if ((aux_flag) && (rangoI == cantAlarmas + 1)){
                                //  rangoI=i;
                                 // Serial.print("Cambio rangoI con i=");
                                 // Serial.println(i);
                                  
                                  
                                //}
                        // }  
                 // }
                //}
        }
 }

void settearAlarmas(){
  if (rangoI == (cantAlarmas + 1)){
    Serial.println("pto control 1");
    contador = 0;
    contadorAux = 0;
    toggleBomba(0);
    toggleAlarma();
  }
  else operacionRangoIn();
}

void operacionRangoIn(){
  if (Hour == alarmaEndHR[rangoI] && Minute == alarmaEndM[rangoI]) {
    toggleBomba(0);
    settear((rangoI*2), (rangoI*4));
  } else {
    toggleBomba(1);
    settear((rangoI), ((rangoI*2)+1));
  }
}

void settear(int cont, int contAux){
  contador = cont;
  contadorAux = contAux;
  toggleAlarma();
}


void toggleBomba(int p){
  switch (p){
    case 0: digitalWrite(pinBomba, HIGH); 
    case 1: digitalWrite(pinBomba, LOW);
    case 2:{
      if (digitalRead(pinBomba)) digitalWrite(pinBomba, LOW);
      else digitalWrite(pinBomba, HIGH);
    }
  }
}

void toggleAlarma(){
  boolean reToggle_flag = false;
  if (contador != cantAlarmas){
      if (contadorAux % 2 == 0){
              if (alarmaDay[contador] == 0 || alarmaDay[contador] == weekday()){
                operacion = alarmaFlag[contador];
                RTC.setAlarm(ALM1_MATCH_HOURS, 0, alarmaStartM[contador], alarmaStartHR[contador], 0);
                RTC.alarm(ALARM_1);
              } else {
                contador++;
                contadorAux++;
                reToggle_flag = true;
              } 
      } else {
          RTC.setAlarm(ALM1_MATCH_HOURS, 0, alarmaEndM[contador], alarmaEndHR[contador], 0);
          RTC.alarm(ALARM_1);
          contador++;
      }
      contadorAux++;
      if (reToggle_flag){
        reToggle_flag = false;
        toggleAlarma();
      }
  } else settearProxAlarma();
}

void settearProxAlarma(){
  if (settearProxAlarma_flag){
    settearProxAlarma_flag = false;
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 5, 0, 0);
    RTC.alarm(ALARM_1);
    toggleAlarma();
  } else {
    settearProxAlarma_flag = false;
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 55, 23, 0);
    RTC.alarm(ALARM_1);
    }
}


void funcionAlarma(){
  if (settearProxAlarma_flag) settearProxAlarma();
  else {
    operarBomba(operacion);
    toggleAlarma();
  }
}

void operarBomba(int op){
 if (digitalRead(pinBomba)){
  toggleBomba(0);
  irAPosicion(0); //posicion inicial
  } else {
  irAPosicion(op);
  toggleBomba(1);
 }
}

void irAPosicion(int pos){
  if (pos == 0){ //posicion inicial
    }
}


void chequeoProxAlarma(){
   if (((Hour == 23) && (Minute >= 56)) || ((Hour == 0) && (Minute <= 4))){
        settearProxAlarma_flag = true;
    }
}


void mostrarEstadoAlarmas(){
  Serial.print("Muestro contador --> ");
  Serial.println(contador);
  Serial.print("Muestro contadorAux --> ");
  Serial.println(contadorAux);
  Serial.print("Muestro weekday --> ");
  Serial.println(weekday());
   Serial.print("Muestro rangoI --> ");
  Serial.println(rangoI);
}









