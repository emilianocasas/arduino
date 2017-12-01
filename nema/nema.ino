#include <LiquidCrystal.h>      

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String cadena;


#define steps 2
#define direccion 3
#define reset  6
#define velocidad  30000


volatile int i = 0;
volatile int hr = 0;
volatile int mins = 0;
volatile boolean posInicial_flag = true;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  lcd.begin(20,4);
  lcd.print("PREPARADO");

  pinMode(19, INPUT_PULLUP);

  pinMode(steps, OUTPUT); 
  pinMode(direccion, OUTPUT); 
  pinMode(reset, OUTPUT);
  digitalWrite(reset, HIGH);

  //while (digitalRead(19)) moverNema(200, HIGH);
  //habilitacionMotor(LOW);
  
    attachInterrupt(4, funcionInt, FALLING);
    algoritmoPosInicial();
    detachInterrupt(4);
}


void loop() {

   
if (Serial2.available()){
    cadena = Serial2.readString();
    Serial.println(cadena);
    mostrarCadenaLCD();
    parsearCadenaLCD();
  }




if (Serial.available()){

    if (posInicial_flag){
      posInicial_flag = false;
      Serial.println("int");
    }
  
    int valor = Serial.read();
    if (valor == 48)  habilitacionMotor(LOW);         
    if (valor == 49)  habilitacionMotor(HIGH);
    if (valor == 50)  moverNema((200), HIGH);
    if (valor == 51)  moverNema((600), LOW);
     if (valor == 52) {
      if (digitalRead(31)) Serial.println("HIGH");
      else Serial.println("LOW"); 
     }
    }

   
}

void moverNema(int pasos, bool direc){ //Pasos(cuanto se va a mover), direccion (i/d), velocidad cte
         digitalWrite(direccion, direc);
         for (int i = 0; i<pasos; i++) {
            digitalWrite(steps, HIGH);  
            digitalWrite(steps, LOW);    
            delayMicroseconds(velocidad);    
          } 
 }

void habilitacionMotor(bool v){
  digitalWrite(reset, v);
  if (v) Serial.println("Motor activado");
  else Serial.println("Motor desactivado");
 }

  void funcionInt(){
    moverNema(0, HIGH);
    posInicial_flag = false;  
  }

  void  algoritmoPosInicial(){
    while (posInicial_flag) moverNema(200, HIGH);
  }


 void mostrarCadenaLCD(){
    int longitudCad = cadena.length();
    String cadenaFinal = cadena.substring(0,(longitudCad - 2));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cadenaFinal);
  }

 void parsearCadenaLCD(){
    int longitudCad = cadena.length();
    String cadenaFinal = cadena.substring(0, 9);
    if (cadenaFinal.equals("moverNema")) {
      habilitacionMotor(HIGH);
      moverNema((200/3), HIGH);
      habilitacionMotor(LOW);
    }
    
  }

