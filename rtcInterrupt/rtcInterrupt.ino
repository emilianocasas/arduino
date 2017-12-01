
#include <Time.h>
#include <TimeAlarms.h>

int volatile a = 0;


void setup(){
  pinMode(2, INPUT);
  pinMode(21, INPUT);
  Serial.begin(9600);
  setTime(8,29,0,1,1,11);
  Alarm.alarmRepeat(8,29,10, MorningAlarm);  
  attachInterrupt(2, funcion, LOW);



}

void  loop(){  
  digitalClockDisplay();
  mostrarVoltajes();
  Alarm.delay(1000); 

  
  if (a == 1){
    Serial.println("Entre en la interrupcion");
  }
  
}


void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");    
  digitalWrite(20, LOW);
  digitalWrite(21, LOW);
//  if 
}


void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void mostrarVoltajes(){
    if (digitalRead(2)) {
      Serial.println("EL 2 esta en HIGH");
    } else {
      Serial.println("EL 2 esta en LOW");
    }
    
    if (digitalRead(21)) {
      Serial.println("EL 21 esta en HIGH");
    } else {
      Serial.println("EL 21 esta en LOW");
    }

}

void funcion(){
a = 1;
}

