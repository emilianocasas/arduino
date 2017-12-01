void Color(int R, int G, int B)
    {     
        analogWrite(9 , R) ;   // Red    - Rojo
        analogWrite(10, G) ;   // Green - Verde
        analogWrite(11, B) ;   // Blue - Azul
    }

void setup(){
    
            pinMode(A0, OUTPUT);
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);
   }
 
void loop()
   {    analogWrite(A0, 255);
   analogWrite(A1, 0);
   analogWrite(A2, 255);
   }
