#include <Servo.h>

Servo leg;
int legPos = 0;

void setup() {
  leg.attach(9);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  if(Serial.available() > 0) {
    String piRead = Serial.readString();
    String servRun = "servo-run";
    if (piRead == servRun) {
      legPos += 30;
      if(legPos > 180) legPos -= 180;
    }
  }
  leg.write(legPos);
  delay(100);
}