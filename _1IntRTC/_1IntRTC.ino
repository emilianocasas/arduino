  #include <LiquidCrystal.h>      // lcd
  #include <SoftwareSerial.h>     //  esp8266
  #include <avr/sleep.h>          //  sleep
  #include <AccelStepper.h>       //  stepper
  #include <Wire.h>               //  wire
  #include <DS3231.h>             //  ds3231
  #include <DS3232RTC.h>          //  ds3231
  #include <Time.h>               //  time
  #include <TimerThree.h>         //  timer1
  #include <TimerOne.h>     

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
  
volatile boolean b = false;
volatile boolean c = false;
volatile boolean flag = false;
volatile int contadorTimer1 = 0;
volatile int contador=0;

 String p[9];
  String m2[9];
  String m3[9];

DS3231 clock;
RTCDateTime dt;

  void setup(void) {
     
    initLCD();
    Serial.begin(9600);
    setSyncProvider(RTC.get);   
    pinMode(A0, OUTPUT);
    pinMode(18, INPUT_PULLUP);
   
    RTC.squareWave(SQWAVE_NONE);
    clock.setDateTime(2015,7,15, 14, 15, 55);  // año mes dia hora minuto segundo
    RTC.setAlarm(ALM1_MATCH_SECONDS, 0, 0, 0, 0);//      segundos, minutos, hora, dia
    RTC.alarm(ALARM_1);
    RTC.alarmInterrupt(ALARM_1, true);
  }

  void loop() {
  
    dt = clock.getDateTime();
    if (RTC.alarm(ALARM_1)) c = true;
   
   if (c){
           contador++;
           zumbador();   
      Serial.print("contador: "); Serial.println(contador);
      Serial.println(clock.dateFormat("d-m-Y H:i:s  ", dt));
      c = false;
    }
 
 

    
  }



 
 
 void initLCD(){
    lcd.begin(20, 4);
    lcd.setCursor(6,2);
    lcd.print(p[0]);
   settearGenerico();  

  }




void zumbador(){
    analogWrite(A0, 255);
    delay(100); 
    analogWrite(A0, 0);
    delay(100);   
    analogWrite(A0, 255);
    delay(100); 
    analogWrite(A0, 0);
    delay(100);   
  }




//Estructura LCD---------------------------------------------------------------------------
  void settearLineas(){
    int i = 0;
    for (i=0; i<4; i++){
      lcd.setCursor(5,i);
      lcd.write(byte(3));  
    }
  }

  void settearFlechas(){
    lcd.setCursor(6,2);
    lcd.write(byte(5));
    lcd.setCursor(19,2);
    lcd.write(byte(4));
  }

  void settearTemperatura(){
    lcd.setCursor(0,3);
    lcd.print("25");
    lcd.setCursor(3,3);
    lcd.write(byte(2));
    lcd.setCursor(4,3);
    lcd.write("C");
  }

  void settearMenuPrincipal(){
    lcd.setCursor(6,0);
    lcd.print("MENU PRINCIPAL");
  }

  void settearGenerico(){
    settearLineas();
    settearFlechas();
    settearTemperatura();
    settearMenuPrincipal();
  }

  void preguntaSiNo(){
    lcd.setCursor(6,3);
    lcd.print("SI");
    lcd.setCursor(18,3);
    lcd.print("NO");
  }
  
  void settearFlechasReloj(){
    lcd.setCursor(0,0);
    lcd.write(byte(8));
    lcd.setCursor(1,0);
    lcd.write(byte(9));
    lcd.setCursor(15,0);
    lcd.write(byte(6));
    lcd.setCursor(15,1);
    lcd.write(byte(7));
  }

  void borrarAccion(int f1, int f2, int c1, int c2){
    int i, d;
    for (i=f1; i<f2; i++){
        for (d=c1; d<c2; d++){
          lcd.setCursor(d,i);
          lcd.write(" ");
        }
    }
  }

 

//Estructura LCD---------------------------------------------------------------------------



