void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
delay(5000);
}

void loop() {
Serial.println("Sleep....");
ESP.deepSleep(10000000);
Serial.println("Woked up....");
}
