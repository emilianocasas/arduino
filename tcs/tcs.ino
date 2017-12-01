#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3

#define S0     7
#define S1     6
#define S2     5
#define S3     4
#define OUT    18

int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor
int a = 0;


//boolean volatile hacerPrueba = 0;
 
 
// Init TSC230 and setting Frequency.

void mostrarTendencia(int a){
  switch (a){
     case 0:
      Serial.println("Tendencia = rojo"); 
     case 1:
      Serial.println("Tendencia = verde");
     case 2:
      Serial.println("Tendencia = azul");    
   }
  
 }


void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
 
  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH); 
}
 
// Select the filter color 
void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
 
  if(Level02 != 0)
    Level02 = HIGH;
 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
 
void TSC_Count()
{
  g_count ++ ;
}
 
void TSC_Callback(){
  int indice=0;
  int maximo = 0;
  int aux=0;
  switch(g_flag)
  {
    case 0: 
         Serial.println("->WB Start");
         TSC_WB(LOW, LOW);              //Filter without Red
         
         break;
    case 1:
         Serial.print("->Frequency R=");
         Serial.println(g_count);
         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            //Filter without Green
         
         break;
    case 2:
         Serial.print("->Frequency G=");
         Serial.println(g_count);
         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);             //Filter without Blue
         
         break;
 
    case 3:
         Serial.print("->Frequency B=");
         Serial.println(g_count);
         Serial.println("->WB End");
         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         
         break;
   default:
         g_count = 0;
   //      terminarPrueba();
      
         break;
  }
  
}
 
void TSC_WB(int Level0, int Level1)      //White Balance
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000);             // set 1s period
}
 
void setup()
{
  TSC_Init();
  Serial.begin(9600);
  Timer1.initialize();             // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback);  
  attachInterrupt(5, TSC_Count, RISING);  
 
  delay(4000);
 

}
 
void loop(){

if (Serial.available()){
  int valor = Serial.read();
  if (valor == 49) hacerPrueba();


}

}


void hacerPrueba(){
  g_flag=0;
  TSC_Init();
  Timer3.initialize();     
  Timer3.attachInterrupt(TSC_Callback);  
  attachInterrupt(5, TSC_Count, RISING);  
  
}

void terminarPrueba(){
  Timer3.detachInterrupt();
  detachInterrupt(5);
  mostrarFrecuencias();
  Serial.println("Se termino de hacer la prueba");
 }


 void mostrarFrecuencias(){
      int a = 0;
    for (a=0; a<3; a++) Serial.println(g_array[a]); 
 }
 





