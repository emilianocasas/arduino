#include <AccelStepper.h>

long currentPos = 0;
int i = 0;
unsigned long posicionActual;
unsigned long posicionTarget;
unsigned long distanciaARecorrer;
int contador = 0;

#define motorPin1  3     // IN1 on the ULN2003 
#define motorPin2  4     // IN2 on the ULN2003 
#define motorPin3  5     // IN3 on the ULN2003 
#define motorPin4  6     // IN4 on the ULN2003 

AccelStepper stepper1(8, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(9600);
   stepper1.setMaxSpeed(1000.0);
   stepper1.setAcceleration(500.0);
   stepper1.setSpeed(900.0);
    stepper1.moveTo(2000.0);
}

void loop() {
  //for (i=0; i<6; i++){
  stepper1.run();
  //delay(1000);
  //}

  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
      posicionActual = (stepper1.currentPosition());
      Serial.print("La posicion actual es ");
      Serial.println(posicionActual);

      posicionTarget = (stepper1.targetPosition());
  Serial.print("El target actual es ");
  Serial.println(posicionTarget);

     distanciaARecorrer = (stepper1.targetPosition());
  Serial.print("La distancia a recorrer es ");
  Serial.println(distanciaARecorrer);
    }
  }
 
 


}







