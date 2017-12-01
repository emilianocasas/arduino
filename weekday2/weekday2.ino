#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 

void setup() {

  Serial.begin(9600);
  setSyncProvider(RTC.get);   


  Serial.println(weekday());
}

void loop() {
}



