#include <Servo.h>

// Leg Servo Data
Servo leg;
int legPin = 9;
int legPos = 0;

// Ball Servo Data
Servo ball;
int ballPin = 8;
int ballPos = 0;

// Motion Sensor Data
int sensorPin = 3;
int val = 0;
int calibrationSequence = 60;

void setup() {
  pinMode(sensorPin, INPUT);
  leg.attach(legPin);
  ball.attach(ballPin);
  
  // Setting up SerialPort for Arduino-><-Pi communication.
  Serial.begin(9600);
  Serial.setTimeout(10);

  // Calibration Sequence for motion sensor.
  for (int i = 0; i < calibrationSequence; i++) {
    Serial.print(".");
    delay(500);
  }
  
  delay(50);
}

void loop() {
  val = digitalRead(sensorPin);

  // If serial port has available messages, read them and execute them.
  if(Serial.available() > 0) {
    String piRead = Serial.readString();
    String servRun = "servo-run";
    if (piRead == servRun) {
      legPos += 90;
      ballPos += 90;
      if(legPos >= 180) legPos = 0;
      if(ballPos >= 180) ballPos = 0;
    }
  }

  // If the sensor is triggered, send message to Pi.
  if(val == HIGH) {
    Serial.print("sensor-execute");
  }

  // Update servo positions
  leg.write(legPos);
  ball.write(ballPos);
  delay(100);
}