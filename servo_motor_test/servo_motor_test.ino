#include <Servo.h>

Servo myMotor;
const int servoPin = 9;
const int middlePoint = 82;
const int leftPoint = middlePoint + 45;
const int rightPoint = middlePoint - 45;

void setup() {
  myMotor.attach(servoPin);
   myMotor.write(leftPoint);
}

void loop() {
//  myMotor.write(leftPoint);
//  delay(5000);
//  myMotor.write(middlePoint);
//  delay(5000);
//  myMotor.write(rightPoint);
//  delay(5000);
}
