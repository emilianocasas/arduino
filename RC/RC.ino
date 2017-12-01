

//int ledPin = 13; // LED is attached to digital pin 13
int x = 0; // variable to be updated by the interrupt

unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void setup() {                
  attachInterrupt(0, increment, FALLING);
  Serial.begin(9600);  //turn on serial communication
}

void loop() {
  //digitalWrite(ledPin, LOW);
  delay(3000); //pretend to be doing something useful
  Serial.println(x, DEC); //print x to serial monitor
}

// Interrupt service routine for interrupt 0
void increment() {
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    x++;
    //digitalWrite(ledPin, HIGH);
    last_button_time = button_time;
  }
}

