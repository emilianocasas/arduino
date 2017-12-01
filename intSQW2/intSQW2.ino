#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
boolean isAlarm = false;
boolean alarmState = false;
int alarmLED = 4;

void alarmFunction(){
isAlarm = true;
}

void setup(){
Serial.begin(9600);
clock.begin();

clock.armAlarm1(false);
clock.clearAlarm1();

clock.setDateTime(2014, 4, 25, 0, 0, 0);

clock.setAlarm1(0, 0, 0, 10, DS3231_MATCH_S);

attachInterrupt(0, alarmFunction, FALLING);


}
void loop(){
dt = clock.getDateTime();
Serial.println(clock.dateFormat("d-m-Y H:i:s - l", dt));
if (isAlarm){
isAlarm = false;
Serial.println("INT");
}
delay(1000);
}
