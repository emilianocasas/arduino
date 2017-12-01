#include <DS3231.h>
#include <Wire.h>
 
DS3231 Clock;
void setup() {
  // Se inicial la interfaz I2c
  Wire.begin();
  // Se inicia la Comunicación Serial
  Serial.begin(9600);
  //Se establece el modo horario en 12 horas (false = 24h)
  Clock.setClockMode(true);
  //Se establece el año
  Clock.setYear((byte)(14));
  //Mes
  Clock.setMonth((byte)05);
  //Dia de la semana (no lo estoy considerando)
  //Clock.setDoW((byte)dia);
  //Día
  Clock.setDate((byte)22);
  //Hora
  Clock.setHour((byte)8);
  //Minutos
  Clock.setMinute((byte)11);
  //Segundos
  Clock.setSecond((byte)0);
}
 
void loop() {
 
}
