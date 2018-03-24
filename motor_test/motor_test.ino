#include <Servo.h>

const int enablePinMotor = 11;
const int controlMotorFront = 7;
const int controlMotorBack = 8;

Servo myServo;
const int servoPin = 10;
const int middlePoint = 82;
const int leftPoint = middlePoint + 55;
const int rightPoint = middlePoint - 50;

int power;
int lpower = 170;
int hpower = 250;

void right();
void left();

void setup() {
  Serial.begin(9600);

  myServo.attach(servoPin);
  myServo.write(middlePoint);

    
  pinMode(enablePinMotor, OUTPUT);
   
  pinMode(controlMotorFront, OUTPUT);
  pinMode(controlMotorBack, OUTPUT);

  digitalWrite(controlMotorFront, LOW);
  digitalWrite(controlMotorBack, HIGH);

  for(power = 150; power < 170; power += 5 ) {
    analogWrite(enablePinMotor, power);    
    delay(5);
  }

  Serial.println(power);
  delay(1000);

  right();
}

void left(){
  delay(100);
  analogWrite(enablePinMotor, hpower);
  //myServo.write(rightPoint + 35);
  delay(100);
  myServo.write(rightPoint + 25);
  delay(100);
  myServo.write(rightPoint + 15);
  delay(50);
  myServo.write(rightPoint + 5);
  delay(200);
  myServo.write(rightPoint);
  analogWrite(enablePinMotor, hpower - 50);
  delay(500);
  analogWrite(enablePinMotor, lpower + 50);
  delay(500);
  analogWrite(enablePinMotor, lpower);
}

void right(){
  
  delay(100);
  analogWrite(enablePinMotor, hpower);
  //myServo.write(leftPoint - 35);
  delay(100);
  myServo.write(leftPoint - 25);
  delay(100);
  myServo.write(leftPoint - 15);
  delay(100);
  myServo.write(leftPoint - 5);
  delay(200);
  myServo.write(leftPoint);
  analogWrite(enablePinMotor, hpower - 50);
  delay(500);
  analogWrite(enablePinMotor, lpower + 50);
  delay(500);
  analogWrite(enablePinMotor, lpower);
}

void loop() {
 // delay(200);
 // right();
//  delay(200);
//  left();
right();
}
