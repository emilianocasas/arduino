#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3

#define pinRele 9
#define S0     7
#define S1     6
#define S2     5
#define S3     4
#define OUT    18
int   g_count = 0;    // Cuenta la frecuencia
int   g_array[3];     // Almacena las frecuencias RGB respectivamente
int   g_flag = 0;     // Organiza la cola de filtros

void setup() {
  Serial.begin(9600);
  pinMode(pinRele, OUTPUT);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49){
        digitalWrite(pinRele, LOW);
     hacerPrueba();
    }
  }
  }

void hacerPrueba(){
  Serial.println("Empieza prueba..");
  g_flag=0;
  TSC_Init();
  Timer1.initialize();     
  Timer1.attachInterrupt(TSC_Callback, 1000000);  
  attachInterrupt(5, TSC_Count, FALLING);  
  }

void TSC_Init(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT_PULLUP);
 
  digitalWrite(S0, HIGH);  // Pone la frecuencia al 2%
  digitalWrite(S1, HIGH); 
}

void TSC_FilterColor(int Level01, int Level02){
  if(Level01 != 0)
    Level01 = HIGH;
 
  if(Level02 != 0)
    Level02 = HIGH;
 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}

void TSC_Callback(){
  int indice=0;
  int maximo = 0;
  int aux=0;
  switch(g_flag){
    case 0: 
         TSC_WB(LOW, LOW);              //Filter without Red
         break;
    case 1:
         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            //Filter without Green
         break;
    case 2:
         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);             //Filter without Blue
         break;
    case 3:
         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         break;
   default:
         terminarPrueba();
         g_count = 0;
         break;
  }
}
 
void TSC_WB(int Level0, int Level1){
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000); 
}

void TSC_Count(){
  g_count ++ ;
}

void terminarPrueba(){
  Timer1.detachInterrupt();
  detachInterrupt(5);
  mostrarFrecuencias();
  Serial.println("Se termino de hacer la prueba");
  pinMode(S0, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  digitalWrite(pinRele, HIGH);
}

 void mostrarFrecuencias(){
    int a = 0;
    for (a=0; a<3; a++) {
       if (a==0) Serial.print("Frecuencia ROJO --> ");
       if (a==1) Serial.print("Frecuencia VERDE --> ");
       if (a==2) Serial.print("Frecuencia AZUL --> ");
       Serial.println(g_array[a]); 
  }
 }
