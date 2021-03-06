 struct TSL{double t; double s; double l;};
 
 int out = 2; 
 int S0 = 7; 
 int S1 = 6; 
 int S2 = 5; 
 int S3 = 4;  
 int sombras_nb = 6; 
 double sombras_val[] = {30.0,60.0,120.0,180.0,240.0,330.0}; 
 char* sombras_id[] = {"rojo","amarillo","verde","cyan","azul","magenta"}; 

void setup() { 
  TCS3210setup();
  Serial.begin(9600);
  Serial.println("Sensor inicializado");
} 

void loop() { 
if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48){
    struct TSL tsl = detectorColor();
    double t = tsl.t; 
    Serial.println(); 

  if (tsl.l < 38.0) { Serial.println("tendencia: negro"); } 
   else if (tsl.s < 4.0 && tsl.l > 60.0) { Serial.println("tendencia: blanco"); } 
   else if (tsl.s < 4.2 && tsl.l > 40.0) { Serial.println("tendencia: gris"); } 
 else 
  if(t>=sombras_val[0] && t<sombras_val[sombras_nb-1]){ 
         for(int idx=0; idx<sombras_nb-1; ++idx){
            if(t>=sombras_val[idx] && t<sombras_val[idx+1]){
            Serial.print("tendencia: ");
            Serial.println(sombras_id[idx+1]);
            break;
    }
  }
   }else{
    Serial.println("tendencia: rojo");
    }
    Serial.println("\n\n");
    } 
  }
}

 void TCS3210setup(){
      pinMode(S0,OUTPUT);
      pinMode(S1,OUTPUT);
      pinMode(S2,OUTPUT);
      pinMode(S3,OUTPUT);
}


struct TSL detectorColor(){
  struct TSL tsl;
  double white = colorRead(out,0);
  double red = colorRead(out,1);
  double blue = colorRead(out,2);
  double green = colorRead(out,3);
  double r,v,b; 
  double offset = 3.0/white; 
  r=min(1.0, offset+(white/red));
  v=min(1.0, offset+(white/green));
  b=min(1.0, offset+(white/blue));
  Serial.print(" Rojo : "); Serial.println( r);
  Serial.print(" verde : "); Serial.println( v);
  Serial.print(" azul : "); Serial.println( b);
  Serial.println();
  double t,s,l;
  double maxRVB = max(max(r, b),v);
  double minRVB = min(min(r, b),v);
  double delta = maxRVB-minRVB;
  double somme = maxRVB+minRVB;
  l=(somme/2.0);
  if(delta==0.0){
      t=s=0.0;
  }else{
      if ( l < 0.5 ) s = delta / somme;
      else s = delta / ( 2.0 - delta );
  double del_R = ( ( ( maxRVB - r ) / 6.0 ) + ( delta / 2.0 ) ) / delta;
  double del_G = ( ( ( maxRVB - v ) / 6.0 ) + ( delta / 2.0 ) ) / delta;
  double del_B = ( ( ( maxRVB - b ) / 6.0 ) + ( delta / 2.0 ) ) / delta;
  if ( r == maxRVB ) t = del_B - del_G;
  else if ( v == maxRVB ) t = ( 1.0 / 3.0 ) + del_R - del_B;
  else if ( b == maxRVB ) t = ( 2.0 / 3.0 ) + del_G - del_R;
  if ( t < 0 ) t += 1.0;
  if ( t > 1 ) t -= 1.0;
  }
  t*=360.0; 
  s*=100.0; 
  l*=100.0; 
  tsl.t=t; tsl.s=s; tsl.l=l;
  Serial.print(" tinte [0..360]: "); Serial.println(t);
  Serial.print(" saturacion [%]: "); Serial.println(s);
  Serial.print(" luminancia [%]: "); Serial.println(l);
  return tsl;
  }

double colorRead(int outPin, int color){
 setMode(2); 
  if(color == 0){
    digitalWrite(S3, LOW); 
    digitalWrite(S2, HIGH); 
  }else if(color == 1){
    digitalWrite(S3, LOW); 
    digitalWrite(S2, LOW); 
  }else if(color == 2){
    digitalWrite(S3, HIGH); 
    digitalWrite(S2, LOW); 
  }else if(color == 3){
    digitalWrite(S3, HIGH); 
    digitalWrite(S2, HIGH); 
  }
  int sensorDelay = 10; //ms
  double readPulse;
  delay(sensorDelay);
  readPulse = pulseIn(outPin, LOW, 1000000);
  if(readPulse < .1) readPulse = 1000000; 
  setMode(0);
  return readPulse;
}

 void setMode(int mode){
    if(mode == 0){
      digitalWrite(S0, LOW); 
      digitalWrite(S1, LOW); 
    }else if(mode == 1){
      digitalWrite(S0, HIGH); 
      digitalWrite(S1, HIGH); 
    }else if(mode == 2){
      digitalWrite(S0, HIGH); 
      digitalWrite(S1, LOW); 
    }else{ if(mode == 3)
      digitalWrite(S0, LOW); 
      digitalWrite(S1, HIGH); 
    }
 }


