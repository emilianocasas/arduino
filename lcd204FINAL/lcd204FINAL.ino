//include---------------------------------------------------------------------------------
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
//include---------------------------------------------------------------------------------  

//creo caracteres especiales---------------------------------------------------------------
  byte temp[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
  };

  byte fArribap1[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100
  };

  byte fAbajop2[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
  };

  byte rainDrop[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000
  };

  byte fIzq[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
  };

  byte fDer[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b11111,
  0b00110,
  0b00100,
  0b00000,
  0b00000
  };

 byte lineaVertical[8] = {
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100
  };

  byte flechaArriba[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100
  };

  byte flechaAbajo[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b11111,
  0b01110,
  0b00100
  };

  byte sol[8] = {
  0b00000,
  0b10101,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00000,
  0b00000
  };
//creo caracteres especiales---------------------------------------------------------------

//define ----------------------------------------------------------------------------------
  #define luzR A0                //led RGB
  #define luzG A1                //led RGB
  #define luzB A2                //led RGB
  #define pinZumbador A7         //zumbador

  //#pinBombaTension             //indicador conexion bomba
  //#pinBombaRele                //on/off bomba
        
  #define pin2 13                //botonera LCD
  #define pin1 15                //botonera LCD
  #define pinEnter 14            //botonera LCD

  #define stepsNEMA 2            //motor
  #define direcNEMA 3           //motor
  #define resetNEMA  6           //motor
  #define velNEMA  30000         //motor
//define ----------------------------------------------------------------------------------

//estructuras datos generales--------------------------------------------------------------
  //sistema-----------------------
  volatile int accion = 0; //accion del lcd
  volatile int cSodioReg = 0;
  volatile int bSodioReg = 0;
  volatile int cloroReg = 0;
  //sistema-----------------------
  
  //timers-----------------------
  volatile int contadorTimer1;
  volatile int contadorTimer3;
  //timers-----------------------

  //nema-------------------------
  volatile boolean posInicial_flag = true;
  //nema-------------------------

  //display----------------------
  LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
  volatile int tempSistema = 0;
  volatile int hrReloj;
  volatile int minReloj;
  volatile int hrRelojAux;
  volatile int minRelojAux;
  volatile boolean alarmasMenu3_flag = false; //flag de navegacion
  volatile boolean settearReloj = false;      //flag de navegacion
  volatile boolean preguntaAlarma = false;    //flag de navegacion
  volatile int menu = 0;
  volatile int contadorReloj=0;
  volatile boolean lluvia = true;
  //display----------------------
  
  //rtc--------------------------
  DS3231 clock; 
  RTCDateTime dt;
  volatile boolean alarma1_flag = false;
  volatile boolean alarma2_flag = false;
  //rtc--------------------------
//estructuras datos generales--------------------------------------------------------------
  
//setup & loop-----------------------------------------------------------------------------
  void setup() {
    initPines();
    //indicadorInitSistema(0);
    initSistemaLCD();
    initComunicacionSerial();

    //algoritmoPosInicial();
    indicadorInitSistema(1);
    primerMensajeLCD();
    //initInterrupcionesGenerales();
    initRTC();
  }

  void loop(){
      obtenerInfoSistema(); //Hora, temperatura, info con necesidad constante.
      if (RTC.alarm(ALARM_1)) alarma1_flag = true;
      if (RTC.alarm(ALARM_2)) alarma2_flag = true;
      if (alarma1_flag) funcionAlarma1();
//      if (alarma2_flag) funcionAlarma2(); //wdt
      if (Serial2.available()) funcionSerial2();
      if (digitalRead(pin2) == 0) funcionPin2();
      if (digitalRead(pin1) == 0) funcionPin1();
      if (digitalRead(pinEnter) == 0) funcionPinEnter();

      

        if ((preguntaAlarma) && (contadorTimer1 == 5)){
          preguntaAlarma = false;
          deshabilitarTimer1();
          normalidad();
        }

      
  }
//setup & loop-----------------------------------------------------------------------------

//inicializacion---------------------------------------------------------------------------
  void indicadorInitSistema(int p){
    if (p) luzVerde();
    else luzAzul();
    //zumbador(3);
  }

  void algoritmoPosInicial(){
    initIntPosInicial();
    habilitacionMotor(HIGH);
    nemaPosInicial();
    moverNema((600), LOW);
    habilitacionMotor(LOW);
  }
  
  void initRTC(){
    initClock();
    settearHora();
    //habilitarIntRTC();
    initAlarmas();
  }
  
  void initComunicacionSerial(){
    Serial.begin(9600);
    Serial2.begin(9600);
  }
  
  void initPines(){
    pinMode(luzR, OUTPUT);  
    pinMode(luzG, OUTPUT);
    pinMode(luzB, OUTPUT);
    pinMode(pinZumbador, OUTPUT);

    pinMode(stepsNEMA, OUTPUT); 
    pinMode(direcNEMA, OUTPUT); 
    pinMode(resetNEMA, OUTPUT);
    
    pinMode(18, INPUT_PULLUP);
    pinMode(19, INPUT_PULLUP);
      
    pinMode(pin2, INPUT_PULLUP);
    pinMode(pin1, INPUT_PULLUP);  
    pinMode(pinEnter, INPUT_PULLUP);
  }

    void initSistemaLCD(){
      lcd.begin(20, 4);
      //lcd.setCursor(0,0);
      //lcd.print("INICIALIZANDO");
      //lcd.setCursor(0,1);
      //lcd.print("SISTEMA");
      //lcd.setCursor(8,1);
      //lcd.blink();  
  }

  void crearCaracteres(){
    lcd.createChar(0, rainDrop);
    lcd.createChar(1, sol);
    lcd.createChar(2, temp);
    lcd.createChar(3, lineaVertical);
    lcd.createChar(4, flechaArriba);
    lcd.createChar(5, flechaAbajo);
    lcd.createChar(6, fArribap1);
    lcd.createChar(7, fAbajop2);
    lcd.createChar(8, fIzq);
    lcd.createChar(9, fDer);
  }
//inicializacion---------------------------------------------------------------------------

//serial(ESP/A)----------------------------------------------------------------------------

 void funcionSerial2(){
  
 }

//serial(ESP/A)----------------------------------------------------------------------------

//interrupciones---------------------------------------------------------------------------

  void initIntPosInicial(){
    attachInterrupt(4, funcionInt, FALLING);
  }

//interrupciones---------------------------------------------------------------------------

//rtc--------------------------------------------------------------------------------------
  void initClock(){
    setSyncProvider(RTC.get);   
    //clock.begin();
  }
  
  void settearHora(){
    clock.setDateTime(2015,7,15, 14, 59, 20);  //año mes dia hora minuto segundo
  }

  void habilitarIntRTC(){ //ver tema dos alarmas, dos interrupciones
    RTC.squareWave(SQWAVE_NONE);
    RTC.alarm(ALARM_1);
    RTC.alarmInterrupt(ALARM_1, true);
  }

  void initAlarmas(){
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 0, 15, 0);//segundos, minutos, hora, dia  
  }

  void obtenerHora(){
    if (hrReloj != dt.hour ||  minReloj != dt.minute){ 
      lcd.noBlink();
      hrReloj = dt.hour;
      minReloj = dt.minute;
      formatoCorrectoHr(2, hrReloj, minReloj, 0, 1, 2, 3, 4, 10, 10);
      if (settearReloj) {
        if (contadorReloj == 0) lcd.setCursor(11,0);
        if (contadorReloj == 1) lcd.setCursor(14,0);
        lcd.blink();
      }
    }
  }

 void funcion1erAlarma(){ 
   preguntaAlarma = true;
   inicializarTimer1();
   funcionMenu8();
  }

  void funcionAlarma1(){
    alarma1_flag = false;
  //  zumbador(2);   
    Serial.print("ALARMA --> "); Serial.println(clock.dateFormat("d-m-Y H:i:s  ", dt));
    funcion1erAlarma();
  }

  void funcionAlarma2(){
    alarma2_flag = false;
    
  }
//rtc--------------------------------------------------------------------------------------

//clima & temperatura----------------------------------------------------------------------
  void rain(){ //cambiar lugar
    lcd.setCursor(18,4);
    lcd.write(byte(0));  
    lcd.setCursor(19,4);
    lcd.write(byte(0));
  }

  void sun(){ //cambiar lugar
    lcd.setCursor(18,4);
    lcd.write(byte(1));  
    lcd.setCursor(19,4);
    lcd.write(byte(1));
  }

  void borrarClima(){ //cambiar lugar
    lcd.setCursor(18,4);
    lcd.write(" ");  
    lcd.setCursor(19,4);
    lcd.write(" ");
  }

  void obtenerTemperatura(){ //Ver tema devolver cursor (blink)
    clock.forceConversion();
    tempSistema = clock.readTemperature();
    lcd.setCursor(0,3);
    lcd.print(tempSistema);
    if (settearReloj) {
        if (contadorReloj == 0) lcd.setCursor(11,0);
        if (contadorReloj == 1) lcd.setCursor(14,0);
        lcd.blink();
      }
    //si la temperatura es peligrosa para el sistema, avisar
  }
//clima & temperatura----------------------------------------------------------------------

//Estructura LCD---------------------------------------------------------------------------
  void obtenerInfoSistema(){
     dt = clock.getDateTime();
     obtenerTemperatura();
     obtenerHora();
  }

   void primerMensajeLCD(){
    borrarAccion(0,4,0,20);
    lcd.noBlink();
    lcd.setCursor(6,2);
    lcd.print("   FILTRAR");
    settearGenerico();  
    crearCaracteres();
  }
  
  void settearLineas(){
    int e = 0;
    for (e=0; e<4; e++){
      lcd.setCursor(5,e);
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
  
  void settearFlechasReloj(int p){
    lcd.setCursor(6,0);  lcd.write(byte(6));
    lcd.setCursor(6,1);  lcd.write(byte(7));
   if (p){ 
    lcd.setCursor(18,1); lcd.write(byte(8));
    lcd.setCursor(19,1); lcd.write(byte(9));
   }
  }

  void borrarAccion(int f1, int f2, int c1, int c2){
    int e, d;
    for (e=f1; e<f2; e++){
        for (d=c1; d<c2; d++){
          lcd.setCursor(d,e);
          lcd.write(" ");
        }
    }
  }

  void moverCostadoReloj(){
    switch (contadorReloj){
      case 0:
        contadorReloj=1;
        lcd.setCursor(14,0);
        lcd.blink();
        break;
      case 1:
        contadorReloj=0;
        lcd.setCursor(11,0);
        lcd.blink();  
        break;
    }
  }

  void moverUpDownReloj(){
    switch (contadorReloj){
      case 0:
        if (hrRelojAux == 23) hrRelojAux = 0;
        else{
          hrRelojAux++;
          formatoCorrectoHr(0, hrRelojAux, 0, 10, 11, 12, 0, 0, 10, 0);
          lcd.setCursor(11,0);
          lcd.blink();
        }
        break;
      case 1:
        if (minRelojAux == 59) {
          minRelojAux = 0;
          contadorReloj = 1;
          moverUpDownReloj();
          contadorReloj = 0;
        }
        else{
          minRelojAux++;
          formatoCorrectoHr(1, 0, minRelojAux, 0, 0, 12, 13, 14, 0, 10);
          lcd.setCursor(14,0);
          lcd.blink();
        }
        break;
    }
  }

  void moverUpDownAlarmas(){
    
  }

  void moverUpDownReservas(){
    
  }
  
   void formatoCorrectoHr(int modo, int h, int m, int p1, int p2, int p3, int p4, int p5, int lh, int lm){ //modo : 0 solo hr, 1 solo min, 2 ambas
         if ((modo == 0) || (modo == 2)){    
              if (h < lh){
                lcd.setCursor(p1,0);
                lcd.write("0");
                lcd.setCursor(p2,0);
              }else{
                lcd.setCursor(p1,0);
              }
              lcd.print(h);
          }
          
          if ((modo == 1) || (modo == 2)){
              if (m < lm){
                lcd.setCursor(p4,0);
                lcd.write("0");
                lcd.setCursor(p5,0);
              }else{
                lcd.setCursor(p4,0);
              }
                lcd.print(m);
           }
           
           lcd.setCursor(p3,0);
           lcd.write(":");         
   }
//Estructura LCD---------------------------------------------------------------------------

//Funciones botones------------------------------------------------------------------------
  void funcionPin2(){
    pulseIn(pin2, HIGH, 300000);
    switch(menu){
      case 0:
        funcionMenu0(1);
        break;
      case 2:
        funcionMenu3();
        break;
      case 3:
        funcionMenu4();
        break;  
      case 4:
        moverCostadoReloj();
        break;
      case 9:
        if (alarmasMenu3_flag){
          alarmasMenu3_flag = false; funcionMenu2();
        } else funcionMenu0(0);
        break;
      default:
        funcionMenu0(0);
        break;    
     }
  }

  void funcionPin1(){
    pulseIn(pin1, HIGH, 300000);
    switch (menu){
      case 1: 
        funcionMenu2();
        break;
      case 2: 
        funcionMenu3();
        break;
      case 3: 
        funcionMenu4();
        break;
      case 4: 
        moverUpDownReloj();
        break;
      case 5: 
        funcionMenu6();
        break;  
      case 9: 
        moverUpDownAlarmas();
        break;
      case 10: 
        moverUpDownReservas();
        break;    
      default: 
        funcionMenu0(2);
        break;  
     }
   }

  void funcionPinEnter(){
    pulseIn(pin1, HIGH, 300000);
    switch (menu){
     case 0: 
      determinarAccionEnter();
      break;
     case 3: 
      alarmasMenu3_flag = true;
      funcionMenu9();
      break;
     case 4: 
      chequearEnterHora(); //Se fija si la hora de finalizacion no es la misma
      break; 
    }
  }

//funciones botones------------------------------------------------------------------------

//funciones menues-------------------------------------------------------------------------
 void funcionMenu0(int f){ //f determina DESDE donde se viene al menu 0
   menu = 0; 
   if (f == 0){
      borrarAccion(0,5,6,20);
      settearMenuPrincipal();
      settearFlechas();
    } else  borrarAccion(2,5,8,19);
    lcd.setCursor(6,3); lcd.write(" ");
    lcd.setCursor(7,3); lcd.write(" ");
    if (f == 0) accion=accion;
      else{
        if (f==2){
           if (accion == 0) accion=10;
           else accion--;
        }else{
           if (accion == 10) accion=0;
           else accion++;
        }
      }  
      lcd.setCursor(7,2); switchAccionRegular();
      if (accion == 7){
          lcd.setCursor(6,3); lcd.print(" (AUTOMATICO)");
      }
       if (accion == 8){
          lcd.setCursor(6,3); lcd.print("   (MANUAL)");
      }
    }

  void funcionMenu1(){ //1
    menu = 1; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("LLUEVE.");
    lcd.setCursor(6,1); lcd.print("CONTINUAR?");
    preguntaSiNo();
  }

  void funcionMenu2(){ //2
    menu = 2; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("   CANCELAR");
    lcd.setCursor(6,1); lcd.print("   POSIBLES");
    lcd.setCursor(6,2); lcd.print("   ALARMAS?");
    preguntaSiNo();
  }

  void funcionMenu3(){ //3
    menu = 3; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("ACTIVAR ALARMA");
    lcd.setCursor(6,1); lcd.print("FINALIZACION?");
    preguntaSiNo();
  }

  void funcionMenu4(){ //4
    menu = 4; borrarAccion(0,4,6,20);
    settearFlechasReloj(1); 
    contadorReloj = 0;
    lcd.setCursor(6,2); lcd.print("  ENTER PARA");
    lcd.setCursor(6,3); lcd.print("  CONFIRMAR");
    hrRelojAux = hrReloj;
    minRelojAux = minReloj;
    formatoCorrectoHr(2, hrRelojAux, minRelojAux, 10, 11, 12, 13, 14, 10, 10);
    lcd.setCursor(11,0);
    lcd.blink();  
    settearReloj = true;
  } 

  void funcionMenu5(){ //5
    menu = 5; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("CONFIRMAR");
    lcd.setCursor(6,1); switchAccionSustantivo();
    lcd.setCursor(6,3);  lcd.print("SI");
    lcd.setCursor(13,3); lcd.print(" VOLVER");
  } 

  void funcionMenu6(){ //6
    menu = 6; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("PREPARANDO");
    lcd.setCursor(6,1); switchAccionRegular();
    lcd.setCursor(13,3); lcd.print("ABORTAR");
  } 

  void funcionMenu7(){ //6
    menu = 6; borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("PREPARANDO");
    lcd.setCursor(6,1); switchAccionRegular();
    lcd.setCursor(13,3); lcd.print("ABORTAR");
  } 

 void funcionMenu8(){ //8, funcion relacionada a alrmas
    lcd.noBlink();
   // menu = 8;
   borrarAccion(0,4,6,20);
    lcd.setCursor(6,0); lcd.print("ALARMA!!");
    lcd.setCursor(6,1); switchAccionSustantivo();
    lcd.setCursor(13,3); lcd.print("ABORTAR");
    preguntaAlarma = true;
    inicializarTimer1();
 }

 void funcionMenu9(){ //9, ver alarmas
    lcd.noBlink();
    menu = 5; borrarAccion(0,4,6,20);
    settearFlechasReloj(0);
    //lcd.setCursor(0,0); lcd.print(cantAlarmas);
    lcd.setCursor(0,2); lcd.print("ALARMAS");
    //mostrarPrimerAlarma();
  }

 void funcionMenu10(){ //10, ver reservas
    lcd.noBlink();
    menu = 5; borrarAccion(0,4,6,20);
    settearFlechasReloj(0);
    //lcd.setCursor(0,0); lcd.print(cantAlarmas);
    lcd.setCursor(0,2); lcd.print("RESERVAS");
    //mostrarPrimerAlarma();
  }
   
  void chequearEnterHora(){
    if ((hrReloj == hrRelojAux) && (minReloj = minRelojAux)){
      lcd.noBlink();
      borrarAccion(2,4, 7, 20);
      lcd.setCursor(6,2);
      lcd.print("  ELIJA OTRA");
      lcd.setCursor(6,3);
      lcd.print("HORA POR FAVOR");
      delay(2000);
      borrarAccion(2,4, 7, 20);
      lcd.setCursor(6,2);
      lcd.print(" ENTER PARA");
      lcd.setCursor(6,3);
      lcd.print(" CONFIRMAR");
      if (contadorReloj == 0) lcd.setCursor(11,0);
      if (contadorReloj == 1) lcd.setCursor(14,0);
      lcd.blink();
      
    } 

    else {
      //nuevaAlarmaApagado(); //lo dispone manualmente el usuario      
      settearReloj = false;
      funcionMenu6();
    }
  }

  void normalidad(){
    Serial.print("menu: "); Serial.println(menu);
    preguntaAlarma = false;
    deshabilitarTimer3();
    switch(menu){
      case 0: 
        funcionMenu0(0);
        break;
      case 1: 
        funcionMenu1();
        break;
      case 2: 
        funcionMenu2();
        break;
      case 3: 
        funcionMenu3();
        break;
      case 4: 
        funcionMenu4();
        break;
      case 6: 
        funcionMenu6();
        break;
      case 7: 
        funcionMenu7();
        break;
      case 8: 
        funcionMenu8();
        break; 
      case 9: 
        funcionMenu9();
        break;   
      case 10: 
        funcionMenu10();
        break; 
      }
  }

  void determinarAccionEnter(){
   switch (accion){
   case 9:
      funcionMenu9();  
      break;
   case 10:
     funcionMenu10();  
      break;
    default:
      if (lluvia) funcionMenu1();
      else funcionMenu2();
      break;
   }
  }

  void switchAccionRegular(){
    switch (accion){
        case 0:
          lcd.print("   FILTRAR");
          break;
        case 1:
          lcd.print("  DESAGOTAR");
          break;
        case 2:
          lcd.print(" RECIRCULAR");
          break;
         case 3:
          lcd.print(" RETROLAVAR");
          break;
         case 4:
          lcd.print("  ENJUAGAR");
          break;
         case 5:
          lcd.print("   TESTEAR");
          break;
         case 6:
          lcd.print("LAVAR FILTRO");
          break;
         case 7:
          lcd.print("REGULAR AGUA");
          break;
         case 8:
          lcd.print("REGULAR AGUA");
          break;
         case 9:
          lcd.print(" VER ALARMAS");
          break;
         case 10:
          lcd.print("VER RESERVAS");
          break;  
       }
  }

  void switchAccionMomentanea(){
    switch (accion){
        case 0:
          lcd.print("    FILTRADO");
          break;
        case 1:
          lcd.print("    DESAGOTE");
          break;
        case 2:
          lcd.print(" RECIRCULACION");
          break;
         case 3:
          lcd.print("  RETROLAVADO");
          break;
         case 4:
          lcd.print("    ENJUAGUE");
          break;
         case 5:
          lcd.print("     TESTEO");
          break;
         case 6:
          lcd.print("LAVADO DE FILTRO");
          break;
         case 7:
          lcd.print("REGULACION");
          break;
         case 8:
          lcd.print("REGULACION ");
          break;
       }
  }

  void switchAccionSustantivo(){
      switch (accion){
        case 0:
          lcd.print("    FILTRADO");
          break;
        case 1:
          lcd.print("    DESAGOTE");
          break;
        case 2:
          lcd.print(" RECIRCULACION");
          break;
         case 3:
          lcd.print("  RETROLAVADO");
          break;
         case 4:
          lcd.print("    ENJUAGUE");
          break;
         case 5:
          lcd.print("     TESTEO");
          break;
         case 6:
          lcd.print("LAVADO DE FILTRO");
          break;
         case 7:
          lcd.print("REGULACION");
          break;
         case 8:
          lcd.print("REGULACION ");
          break;
       }
  }
  
//funciones menues-------------------------------------------------------------------------

//nema-------------------------------------------------------------------------------------
  
  void moverNema(int pasos, bool direc){ //Pasos(cuanto se va a mover), direccion (i/d), velocidad cte
         digitalWrite(direcNEMA, direc);
         for (int i = 0; i<pasos; i++) {
            digitalWrite(stepsNEMA, HIGH);  
            digitalWrite(stepsNEMA, LOW);    
            delayMicroseconds(velNEMA);    
          } 
 }

  void habilitacionMotor(bool f){
    digitalWrite(resetNEMA, f);
    if (f) Serial.println("Motor activado");
    else Serial.println("Motor desactivado");
  }

  void funcionInt(){
    moverNema(0, HIGH);
    posInicial_flag = false;  
  }

  void  nemaPosInicial(){
    while (posInicial_flag) moverNema((200/3), HIGH);
    habilitacionMotor(LOW);
  }

//nema-------------------------------------------------------------------------------------

//timers-----------------------------------------------------------------------------------
  void inicializarTimer1(){
    Timer1.initialize();
    Timer1.attachInterrupt(contarTimer1, 1000000);
  }

  void inicializarTimer3(int n){
    Timer3.initialize();
    Timer3.attachInterrupt(contarTimer3, 1000000);
  }

  void contarTimer1(){
    contadorTimer1++;
    Serial.println(contadorTimer1);
  }

  void contarTimer3(){
    contadorTimer3++;
  }

  void initTimerAlarma(){
    preguntaAlarma = true;
    inicializarTimer3(1000000);
   }

  void deshabilitarTimer1(){
    Timer1.detachInterrupt();
    contadorTimer1 = 0;
  }

  void deshabilitarTimer3(){
    Timer3.detachInterrupt();
    contadorTimer3 = 0;
  }
  
//timers-----------------------------------------------------------------------------------

//zumbador---------------------------------------------------------------------------------
void zumbador(int n){
  int e = 0;
    for (e=0; e<n; e++){
      analogWrite(pinZumbador, 255);
      delay(100); 
      analogWrite(pinZumbador, 0);
      delay(100);
    }
  }
//zumbador---------------------------------------------------------------------------------

//led rgb----------------------------------------------------------------------------------

 void luzVerde(){
  analogWrite(luzR, 255);
  analogWrite(luzG, 0);
  analogWrite(luzB, 255);
}

void luzRoja(){
  analogWrite(luzR, 0);
  analogWrite(luzG, 255);
  analogWrite(luzB, 255);
}

void luzAzul(){
  analogWrite(luzR, 255);
  analogWrite(luzG, 225);
  analogWrite(luzB, 0);
}


//led rgb----------------------------------------------------------------------------------









