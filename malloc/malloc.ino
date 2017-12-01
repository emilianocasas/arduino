
#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 

#define pinBomba 10

DS3231 clock;
RTCDateTime dt;

char* alarmaFlag;
int* alarmaStartHR;
int* alarmaStartM;
int* alarmaEndHR;
int* alarmaEndM;
int* alarmaDay;
int* cantAlarmasDia;

volatile int Hour;
volatile int i;
volatile int Minute;
volatile int cantAlarmas;
volatile int rangoI;
volatile int contador;
volatile int contadorAux;
volatile char operacion;
volatile boolean settearProxAlarma_flag = false;

void setup() {
  //-------------------
  Serial.begin(9600);
  //-------------------
  int* alarmaStartHR = devolverPunteroInt(7);
  int* alarmaStartM = devolverPunteroInt(7);
  int* alarmaEndHR = devolverPunteroInt(7);
  int* alarmaEndM = devolverPunteroInt(7);
  int* alarmaDay = devolverPunteroInt(7);
  int* cantAlarmasDia = devolverPunteroInt(7);
  char* alarmaFlag = devolverPunteroChar(7); 
  //------------------
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
  alarmaDay[0]= 3;
  alarmaDay[1]= 1;
  alarmaDay[2]= 7;
  alarmaDay[3]= 0;
  alarmaDay[4]= 8;
  alarmaDay[5]= 0;
  alarmaDay[6]= 2;
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
  
  Hour = 11;
  Minute = 0;


  
 // chequeoProxAlarma();
 // if (settearProxAlarma_flag ) settearProxAlarma(alarmaDay, alarmaStartHR, alarmaEndHR, alarmaStartM, alarmaEndM, alarmaFlag);
 // else obtenerRango(alarmaDay, alarmaStartHR, alarmaEndHR, alarmaStartM, alarmaEndM );
 obtenerRango(alarmaDay, alarmaStartHR, alarmaEndHR, alarmaStartM, alarmaEndM );
 settearAlarmas(alarmaDay, alarmaStartHR, alarmaEndHR, alarmaStartM, alarmaEndM, alarmaFlag);

//  mostrarEstadoAlarmas();
  setSyncProvider(RTC.get);   
Serial.println(weekday());
}

void loop() {

  if (RTC.alarm(ALARM_1)) {
     funcionAlarma(alarmaDay, alarmaStartHR, alarmaEndHR, alarmaStartM, alarmaEndM, alarmaFlag);
  }    

}

int* devolverPunteroInt(int n){
   n = (sizeof(int)) * n;
  int* pointer = (int *)malloc(n);
   return pointer;
  }
  
char* devolverPunteroChar(int n){
   n = (sizeof(char)) * n;
   char* pointer = (char *)malloc(n);
   return pointer;
}

void cargarPuntero(int *p){
  p[0] = 0;
  p[1] = 1;
  p[2] = 2;
  p[3] = 3;
}


void liberarPuntero(int *p){
  free(p);
}


void mostrarPuntero(){
  for (i=0; i<7; i++){
    Serial.println(alarmaDay[i]);
  }
}

void obtenerRango(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM){
   boolean aux_flag = true;
             for (i=0; i<7; i++){
               Serial.println();
               Serial.println();
                if (rangoI == cantAlarmas + 1){
                    if (aDay[i] == 0 || aDay[i] == weekday()){ //Si la alarma debe ser ejecutada en el dia actual
                      Serial.print("Hasta aca entre con i= "); Serial.println(i);
                        if ((aSHR[i] <= Hour) && (Hour <= aEHR[i])){  //Si la hora actual es igual a la de la start o end de la alarma
                            Serial.print("Denuevo, hasta aca entre con i= "); Serial.println(i);
                             if (aSHR[i] == Hour){
                                  if (aSM[i] <= Minute){
                                      rangoI = i;
                                      Serial.print("1-Cambio a rangoI con i= "); Serial.println(i);
                                  } else aux_flag = false;
                              }
                              if (aEHR[i] == Hour){
                                  if (aEM[i] >= Minute){
                                  rangoI = i;
                                  Serial.print("2-Cambio a rangoI con i= "); Serial.println(i);
                                  } else  aux_flag = false;
                              }
                              if ((aux_flag) && (rangoI == cantAlarmas + 1)){
                                rangoI=i;
                                Serial.print("3-Cambio a rangoI con i= "); Serial.println(i);
                              }
                         }  
                     }
                }
              }
 }

void settearAlarmas(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  if (rangoI == (cantAlarmas + 1)){
    contador = 0;
    contadorAux = 0;
    toggleBomba(0);
    toggleAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
  } else operacionRangoIn(aDay, aSHR, aEHR, aSM, aEM, aF);
}

void operacionRangoIn(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  if (Hour == aEHR[rangoI] && Minute == aEM[rangoI]) {
    toggleBomba(0);
    settear((rangoI*2), (rangoI*4), aDay, aSHR, aEHR, aSM, aEM, aF);
  } else {
    toggleBomba(1);
    settear((rangoI), ((rangoI*2)+1), aDay, aSHR, aEHR, aSM, aEM, aF);
  }
}

void settear(int cont, int contAux, int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  contador = cont;
  contadorAux = contAux;
  toggleAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
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

void toggleAlarma(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  boolean reToggle_flag = false;
  if (contador != cantAlarmas){
      if (contadorAux % 2 == 0){
              if (aDay[contador] == 0 || aDay[contador] == weekday()){
                operacion = aF[contador];
                RTC.setAlarm(ALM1_MATCH_HOURS, 0, aSM[contador], aSHR[contador], 0);
                RTC.alarm(ALARM_1);
              } else {
                contador++;
                contadorAux++;
                reToggle_flag = true;
              } 
      } else {
          RTC.setAlarm(ALM1_MATCH_HOURS, 0, aEM[contador], aEHR[contador], 0);
          RTC.alarm(ALARM_1);
          contador++;
      }
      contadorAux++;
      if (reToggle_flag){
        reToggle_flag = false;
        toggleAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
      }
  } else settearProxAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
}

void settearProxAlarma(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  if (settearProxAlarma_flag){
    settearProxAlarma_flag = false;
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 5, 0, 0);
    RTC.alarm(ALARM_1);
    toggleAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
  } else {
    settearProxAlarma_flag = false;
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 55, 23, 0);
    RTC.alarm(ALARM_1);
    }
}


void funcionAlarma(int *aDay, int *aSHR, int *aEHR, int *aSM, int *aEM, char* aF){
  if (settearProxAlarma_flag) settearProxAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
  else {
    operarBomba(operacion);
    toggleAlarma(aDay, aSHR, aEHR, aSM, aEM, aF);
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










