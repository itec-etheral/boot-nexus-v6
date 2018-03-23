#include <Servo.h>

const int enablePinMotor =11;
const int controlMotorFront = 8;
const int controlMotorBack = 7;

Servo myServo;
const int servoPin = 10;
const int middlePoint = 82;
const int leftPoint = middlePoint + 50;
const int rightPoint = middlePoint - 50;

int power;

void setup() {
  Serial.begin(9600);

  myServo.attach(servoPin);
  myServo.write(middlePoint);

    
  pinMode(enablePinMotor, OUTPUT);
   
  pinMode(controlMotorFront, OUTPUT);
  pinMode(controlMotorBack, OUTPUT);

  digitalWrite(controlMotorFront, HIGH);
  digitalWrite(controlMotorBack, LOW);

  for(power = 146; power < 150; power += 5 ) {
    analogWrite(enablePinMotor, power);    
    delay(5);
  }

  Serial.println(power);
  delay(1000);
}

void loop() {
  //delay(2000);
  delay(100);
  myServo.write(rightPoint + 15);
  analogWrite(enablePinMotor, 250);
  delay(100);
  myServo.write(rightPoint + 5);
  delay(1500);
  myServo.write(rightPoint);
  analogWrite(enablePinMotor, 160);
  
  delay(2000);
  
  delay(100);
  analogWrite(enablePinMotor, 250);
  myServo.write(leftPoint - 15);
  delay(100);
  myServo.write(leftPoint - 5);
  delay(1500);
  myServo.write(leftPoint);
  analogWrite(enablePinMotor, 160);
  delay(2000);
}
