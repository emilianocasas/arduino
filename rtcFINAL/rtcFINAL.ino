#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define pinSi 31
#define pinNo 33
#define pinArriba 14
#define pinAbajo 15
#define pinRealizar 16
#define pinZumbador A0
#define pinInit A1

String p[8];

volatile boolean enterFlag = false;
volatile boolean flag = false;
volatile boolean b = false;
volatile boolean c= false;
volatile boolean f = false;
volatile boolean alarmaActual = false;
volatile boolean ledAPrendido = false;
volatile boolean inicioAccion_flag = false;
volatile boolean sleepFlag = false; 
volatile boolean ardDespierto_flag = false; 
volatile boolean alarmaInterrumpida = false; //Se habilita si se hizo un pedido de accion, no si esta despierto, pq podria ser que la persona lo prendio pero lo dejo asi. En ese caso, luego la alarma lo apagara o se encargara la alarma 2 (wdt).                                            
volatile int i = 0;

DS3231 clock;
RTCDateTime dt;

void setup(void) {
  inicializacionPines();
  indicadorInicializacion();
  inicializacionRTC();
  inicializacionSerial();
  inicializacionInterrupciones();
  incializacionLCD();
  sleep();
}

void loop() {
  dt = clock.getDateTime();

  if (digitalRead(pinArriba) == 0)     funcionPinArriba();
  if (digitalRead(pinAbajo) == 0)      funcionPinAbajo();
  if (digitalRead(pinRealizar)== 0)   funcionPinRealizar();
  if (digitalRead(pinSi)== 0)         funcionPinSi();
  if (digitalRead(pinNo)== 0)         funcionPinNo();

  if (RTC.alarm(ALARM_1)) {
    alarmaActual = true;
    b = true;
  }
       
  if (b){ //Operacion que debe realizar la alarma
    b = false;
    zumbador();
    if (alarmaInterrumpida == 0){
     if (ardDespierto_flag) preguntarSiAlarma(); //No hay int de alarma, pero ya estaba despierto, hay que preguntar.  
     else funcionAlarma(); //No estaba int la alarma y tampoco despierto desde antes (entonces no se tiene q preguntar).
    }
    flag = true;
   }

 if ((c) && (flag)){
    //zumbador();
    flag = false;
    c = 0;
    delay(1000);
    delay(1000);
    sleep();
  }
}

//--------------------------------------------------------------

void indicadorInicializacion(){
  analogWrite(pinInit, HIGH);
}

void inicializacionPines(){
  pinMode(pinInit, OUTPUT);
  pinMode(pinSi, INPUT_PULLUP);
  pinMode(pinNo, INPUT_PULLUP);  
  pinMode(pinArriba, INPUT_PULLUP);
  pinMode(pinAbajo, INPUT_PULLUP);  
  pinMode(pinRealizar, INPUT_PULLUP);
  pinMode(pinZumbador, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
}

void inicializacionRTC(){
  setSyncProvider(RTC.get);   
  RTC.squareWave(SQWAVE_NONE);
  //clock.setDateTime(2015,8,28, 0, 34, 59); // año mes dia hora minuto segundo
  RTC.setAlarm(ALM1_MATCH_SECONDS, 10, 0, 0, 0); // segundos, minutos, hora, dia
  RTC.alarm(ALARM_1);
  RTC.alarmInterrupt(ALARM_1, true);
}

void inicializacionSerial(){
    Serial.begin(9600);  
}

void incializacionLCD(){
  lcd.begin(16, 2);
  p[0] = "FILTRAR";
  p[1] = "DESAGOTAR";
  p[2] = "RECIRCULAR";
  p[3] = "RETROLAVAR";
  p[4] = "ENJUAGAR";
  p[5] = "TESTEAR";
  p[6] = "LAVAR FILTRO";
  p[7] = "HACER PRUEBA";
}

void inicializacionInterrupciones(){
  attachInterrupt(0, wake, FALLING);
}

void sleep(){
    sleepFlag = true;
    lcd.clear();
    lcd.print("Me voy a dormir");
    delay(1000);
    delay(1000);
    lcd.clear();
    lcd.print("Sleep");
    delay(100);
    sleepNow();
  }
 
 void wake(){
  sleepFlag = false;
  nuevaInt();
  c = 1;
  lcd.clear();
  lcd.print("wake");
  delay(1500);
  lcd.clear();
  detachInterrupt(0);
 }

void sleepNow(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();    
   attachInterrupt(0,wake, LOW); 
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
 }


void zumbador(){
    analogWrite(pinZumbador, 255);
    delay(100); 
    analogWrite(pinZumbador, 0);
    delay(100);   
    analogWrite(pinZumbador, 255);
    delay(100); 
    analogWrite(pinZumbador, 0);
    delay(100);   
  }


void chequeoAlarmasActuales(){ //Si hay alarmas actuales, preguntar si desea abortar. Si se desea hacer una accion, preguntar
                               // si se desean abortar posibles alarmas en ese lapso de tiempo.
  //if (alarmaActual)
}

void funcionAlarma(){
  lcd.clear();
  lcd.print(clock.dateFormat("d-m-Y H:i:s  ", dt));
}

void nuevaInt(){
 attachInterrupt(5, funcionAlarma, FALLING); 
}

void funcionAlarmaInt(){
 ardDespierto_flag = true; 
}

void preguntarSiAlarma(){
  lcd.clear();
  lcd.print("Ejecutar alarma??");
}

void funcionPinArriba(){
  pulseIn(14, HIGH, 300000);
      if (i<7){
       lcd.clear();
       i++;
       delay(100);
       lcd.print(p[i]);
       }
}

void funcionPinAbajo(){
   pulseIn(15, HIGH, 200000);
     if (i>0){ 
      lcd.clear();
      i--;
      delay(100);
      lcd.print(p[i]);
     }
}

void funcionPinRealizar(){
   pulseIn(16, HIGH, 200000);
        lcd.clear();
        lcd.print("CONFIRMAR ACCION");
        lcd.setCursor(0,1);
        lcd.print(p[i] + " ?"); 
        enterFlag = true;
}

void funcionPinSi(){
  if (enterFlag){
         lcd.clear();
         enterFlag = false;
         lcd.print("Empezando..");
      }
}

void funcionPinNo(){
  if (enterFlag){
         enterFlag = false;
        lcd.clear();
         lcd.print(p[i]);
      }
}









