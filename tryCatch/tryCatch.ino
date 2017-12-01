volatile int e = 5;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
    try{
    e = 5;
  }
  catch (int e){
    Serial.println(e);
  }

}
