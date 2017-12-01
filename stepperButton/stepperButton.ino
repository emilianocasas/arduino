#include <AccelStepper.h>
#define HALFSTEP 8
int i = 0;
int d=2;

// Motor pin definitions
#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10     // IN3 on the ULN2003 driver 1
#define motorPin4  11    // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.moveTo((4070)/6);

}

void loop() {

  d=digitalRead(2);

  if (d==0){
    digitalWrite(13,HIGH);
    stepper1.run();
  }
 else digitalWrite(13,LOW);
  
  
  if (Serial.available()){
   
  
    int valor = Serial.read();
    if (valor == 49){
  
    stepper1.move((4070)/6);
    
    
    }
  }
}
