//----------------------------INCLUYO LIBRERIAS NECESARIAS----------------------------------
#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3
//----------------------------INCLUYO LIBRERIAS NECESARIAS--------------------------------//

//-----------------------DEFINO CONSTANTES Y VARIABLES GLOBALES-----------------------------

#define luzR A0      
#define luzG A1    
#define luzB A2     

#define motorPin1  31      // IN1 stepper
#define motorPin2  33     // IN2 stepper
#define motorPin3  35     // IN3 stepper
#define motorPin4  37      // IN4 stepper

AccelStepper stepper1(8, motorPin1, motorPin3, motorPin2, motorPin4);
# define pinStepper 8

boolean volatile preSleepFlag = false;
boolean volatile sleepFlag = false;

boolean volatile hacerPrueba_flag = false;
boolean volatile f = true;

int volatile b = 0; 
int volatile contador = 0;     

DS3231 clock;
RTCDateTime dt;

SoftwareSerial esp8266(0,1); 

#define pinZumbador A7


#define pinTCS 5
#define pinPrenderTCS 6
#define pinIntTCS 3
#define S0     53
#define S1     51
#define S2     49
#define S3     47
#define OUT    18
int   g_count = 0;    // Cuenta la frecuencia
int   g_array[3];     // Almacena las frecuencias RGB respectivamente
int   g_flag = 0;     // Organiza la cola de filtros

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);
  sleep();
}

void loop(){

if (sleepFlag == 0){

if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48)  Serial.println("hola");
}

  if (contador == 2 ){
    deshabilitarTimer1();
    contador = 0;
    habilitarIntSleep();
    Serial.println("int habilitada");
  }

}else{
  sleepFlag = false;
  Serial.println("Me duermo");
  delay(500);
    sleepNow();
 }
}

void sleep(){
  digitalWrite(5, LOW);
 deshabilitarIntSleep();
  sleepFlag = true;
  }

void sleepNow(){
  
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(0,wakeBoton, LOW); 
    attachInterrupt(1,wakeBoton, LOW); 
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
 }

 void habilitarIntSleep(){
  attachInterrupt(0,sleep, FALLING) ;
  Serial.println("me despierto");
}

void deshabilitarIntSleep(){
  detachInterrupt(0);
}


void inicializarTimer1(){
  Timer1.initialize();
  Timer1.attachInterrupt(contar, 1000000);
}

void inicializarTimer12(){
  Timer1.initialize();
  Timer1.attachInterrupt(contar, 100000);
}

void contar(){
  contador++;
}

void deshabilitarTimer1(){
  Timer1.detachInterrupt();
  contador = 0;
}

void wakeBoton(){
 detachInterrupt(1); 
  detachInterrupt(0);         // Elimina interrupciones wake
  digitalWrite(5, HIGH);
  inicializarTimer1();
 
}

