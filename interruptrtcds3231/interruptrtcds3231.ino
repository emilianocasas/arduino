 #include <Wire.h>
 #include <DS3231.h>
  DS3231 clock;
  RTCDateTime dt;
int volatile a = 0;

void setup() {
  clock.begin();
  pinMode(2, INPUT);
  Serial.begin(9600);
  clock.armAlarm1(false);
 
  clock.clearAlarm1();
  //clock.setDateTime(2014, 4, 25, 0, 0, 0);
  clock.setAlarm1(0, 0, 0, 20, DS3231_MATCH_S);
  //attachInterrupt(0, funcion, FALLING);

}

void loop() {
  dt = clock.getDateTime();
 
  
  Serial.print(clock.dateFormat("d-m-Y H:i:s                   ", dt));
  
  if (a){
    a = 0;
    Serial.println("Entre en la interruptcion");
  }

   if (clock.isAlarm1()){
    Serial.println("ALARM 1 TRIGGERED!");
  }
   
 
      if (digitalRead(2)) Serial.println("2 EN HIGH");
      else Serial.println("2 EN LOW");
    
  
  delay(1000);
}

void funcion(){
  a = 1;
}

