#include <TimerOne.h>

#define pinRele 9
#define S0     7
#define S1     6
#define S2     5
#define S3     4
#define OUT    18

int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor

void TSC_Init() // Init TSC230 and setting Frequency.
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(pinRele, OUTPUT);
  pinMode(OUT, INPUT_PULLUP);

  digitalWrite(pinRele, LOW);
 
  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH); 
}

void mostrarTendencia(int a){
  if (a == 0)
  Serial.println("Tendencia = rojo"); 
  
   if (a == 1)
  Serial.println("Tendencia = verde"); 
  
   if (a == 2)
  Serial.println("Tendencia = azul"); 
}

void TSC_FilterColor(int Level01, int Level02)      // Select the filter color 
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
  int indice = 0;
  int maximo = 0;
  int aux = 0;
  switch(g_flag) {
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
    
         
         
         //mostrarTendencia(aux);
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         break;
  
   default:
         g_count = 0;
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
 
void setup(){
  TSC_Init();
  Serial.begin(9600);
  Timer1.initialize(3000000);             // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback);  
  attachInterrupt(5, TSC_Count, CHANGE);  
  delay(4000);
}
 
void loop(){
   g_flag = 0;
   delay(4000);
}


