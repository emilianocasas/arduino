boolean volatile a = 0;
int d=2;   

void funcion(){
  a = true;  
}



void setup(){
  Serial.begin(9600);
pinMode(2,INPUT);
pinMode(13,OUTPUT);
attachInterrupt(0, funcion, FALLING);

}
void loop(){
d=digitalRead(2);
if(d==0)
digitalWrite(13,HIGH);
else
digitalWrite(13,LOW);


if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49) {
      if (digitalRead(2)) Serial.println("El pin 2 esta en HIGH");
      else Serial.println("El pin 2 esta en LOW");
    }
  }

if (a) Serial.println("Entre en la interrupcion");
  
}
