//----------------------------INCLUYO LIBRERIAS NECESARIAS----------------------------------
#include <TimerThree.h>         //  Para los timers
#include <TimerOne.h>         //  Para los timers
#include <SoftwareSerial.h>     //  Para el esp8266-07
#include <avr/sleep.h>          //  Para dormir al arduino
#include <AccelStepper.h>       //  Para el stepper
//----------------------------INCLUYO LIBRERIAS NECESARIAS--------------------------------//

//-----------------------DEFINO CONSTANTES Y VARIABLES GLOBALES-----------------------------

# define pinRojo  9   //Dormido
# define pinVerde 10  //Despierto

# define testear    22    //
# define retolavar  23    //
# define filtrar    24    //
# define enjuagar   25    //
# define desagotar  26    //

#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10     // IN3 on the ULN2003 driver 1
#define motorPin4  7    // IN4 on the ULN2003 driver 1

int volatile a = 0; 
int volatile b = 0; 
int contador = 0;     

AccelStepper stepper1(8, motorPin1, motorPin3, motorPin2, motorPin4);

boolean volatile conexionSerial;
SoftwareSerial esp8266(3,2); 

#define S0     7
#define S1     6
#define S2     5
#define S3     4
#define OUT    18
int   g_count = 0;    // Cuenta la frecuencia
int   g_array[3];     // Almacena las frecuencias RGB respectivamente
int   g_flag = 0;     // Organiza la cola de filtros



//-----------------------DEFINO CONSTANTES Y VARIABLES GLOBALES---------------------------//

//---------------------------------------SETUP----------------------------------------------

void setup(){
  inicializarPines();
  inicializarComunacionSerial();
  inicializarInterrupciones();
  inicializarStepper();
  sleep();
}

//---------------------------------------SETUP--------------------------------------------//

//---------------------------------------LOOP-----------------------------------------------
void loop(){

  stepper1.run();

  if (digitalRead(3)) a = a;
  else moverStepper();
  
 if (Serial.available()) {
    int val = Serial.read();
   
    if (val == 'A') Serial.println("Hola"); 
    
    if (val == 48) moverStepper();  

    if (val == 49)  hacerPrueba();
    }

    if (a == 1){
    Timer1.detachInterrupt();
    detachInterrupt(0); 
    contador = 0;
    a = 0;
    Serial.println("Serial: Entering Sleep mode");
    //hagoTiempo();
    delay(1000);
    delay(1000);
    delay(1000);
    sleepNow();     
  }

    if (b == 1){
  Timer1.initialize();
  Timer1.attachInterrupt(contar, 1000000);
  }

  if (contador == 3) {
    contador = 0;
    attachInterrupt(0,sleep, FALLING) ;
  }
  
}

//---------------------------------------LOOP---------------------------------------------//

//----------------------------------INICIALIZACION------------------------------------------

void inicializarPines(){
  pinMode(2, INPUT); 
  pinMode(3, INPUT);
  pinMode(pinVerde, OUTPUT);

}

void inicializarComunacionSerial(){
  esp8266.begin(19200);
  Serial.begin(9600);

}

void inicializarInterrupciones(){

}

//----------------------------------INICIALIZACION----------------------------------------//

//--------------------------------- FUNCIONES SLEEP-----------------------------------------

void sleep(){
 apagarPinVerde();
 prenderPinRojo();
 a = 1;
}

void sleepNow(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(0,wakeBoton, LOW); 
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
 }

void contar(){
  contador++;
}

//--------------------------------- FUNCIONES SLEEP---------------------------------------//


//--------------------------------- FUNCIONES WAKE------------------------------------------

void wakeBoton(){
   b = 1;
   apagarPinRojo();
   prenderPinVerde();
   mostrarMensaje();
}
 
void wakeEsp(){
  conexionSerial = true;
}

void wakeRTC(){
  conexionSerial = true;
}

void mostrarMensaje(){
  Serial.println("Me desperte vieja, no me importa nada");
}

//--------------------------------- FUNCIONES WAKE---------------------------------------//

//------------------------------PRENDER Y APAGAR LEDS--------------------------------------

void prenderPinVerde(){
  digitalWrite(pinVerde, HIGH);
}

 void apagarPinVerde(){
  digitalWrite(pinVerde, LOW);
}

void prenderPinRojo(){
    pinMode(pinRojo, INPUT);
}

void apagarPinRojo(){
  pinMode(pinRojo, OUTPUT);
}

//------------------------------PRENDER Y APAGAR LEDS------------------------------------//

//-------------------------------FUNCIONES TCS3200-----------------------------------------




//-------------------------------FUNCIONES TCS3200-----------------------------------------


void hacerPrueba(){
  g_flag=0;
  TSC_Init();
  Timer3.initialize();     
  Timer3.attachInterrupt(TSC_Callback);  
  attachInterrupt(5, TSC_Count, RISING);  
  }

void TSC_Init(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
 
  digitalWrite(S0, LOW);  // Pone la frecuencia al 2%
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
         terminarPrueba();
         g_count = 0;
         break;
  }
}
 
void TSC_WB(int Level0, int Level1){
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
}

void TSC_Count(){
  g_count ++ ;
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

//-------------------------------FUNCIONES TCS3200---------------------------------------//

//-------------------------------FUNCIONES HC-SR04-----------------------------------------

void medirDistancia(){
 // inicializarPinesHC();
//  dispararYRecibir();
}

void inicializarPinesHC(){
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

//-------------------------------FUNCIONES HC-SR04---------------------------------------//

//-------------------------------FUNCIONES STEPPER-----------------------------------------

//-------------------------------FUNCIONES STEPPER---------------------------------------//

//-------------------------------FUNCIONES SERVOS------------------------------------------

//-------------------------------FUNCIONES SERVOS----------------------------------------//

//-------------------------------FUNCIONES STEPPER-----------------------------------------

void  inicializarStepper(){
   stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.move((4070)/6);
  
}

void moverStepper(){
  
  stepper1.move((4070)/6);
    stepper1.run();
}

//-------------------------------FUNCIONES STEPPER---------------------------------------//


















 

 
