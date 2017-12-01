//El negro va a tierra, rojo vcc y blanco al pin

#include <Servo.h>
 
Servo myservo; 
Servo myservo2;
int pos = 0;

void setup(){
myservo.attach(11);
myservo2.attach(10);
Serial.begin(9600);
myservo.write(0);
myservo2.write(0);
delay(1000);
}
void loop(){
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
             {                                  // in steps of 1 degree 
            myservo.write(pos);     
            myservo2.write(pos);// tell servo to go to position in variable 'pos' 
              delayMicroseconds(5000);                       // waits 15ms for the servo to reach the position 
           } 
         for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
          {                                
          myservo.write(pos);     
            myservo2.write(pos);             // tell servo to go to position in variable 'pos' 
          delayMicroseconds(5000);                       // waits 15ms for the servo to reach the position 
          } 
    }
    
  }

}  
