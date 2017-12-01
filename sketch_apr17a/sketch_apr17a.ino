


void setup() {
  
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int val = Serial.read()-48;
  switch(val)
  {
    case 1: 
    digitalWrite(13, HIGH);
    break;
    
    case 2: 
    digitalWrite(13, LOW);
    break;
}
}
