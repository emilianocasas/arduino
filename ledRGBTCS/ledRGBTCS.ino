#define red A0
#define green A1
#define blue A2

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, 255);
  digitalWrite(green,0 );
  digitalWrite(blue, 255);
}

void loop() {
  // put your main code here, to run repeatedly:

}
