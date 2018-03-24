#include <Servo.h>

//Front motor pins
const int hEnablePin = 11;
const int controlMotorBack = 7;
const int controlMotorFront = 8;

//servo 
Servo backServo;
const int servoAnglePin = 10;
const int middleAngle = 82;
const int leftAngle = middleAngle + 40;
const int rightAngle = middleAngle - 30;

// sensor
const int leftSensorPin = A0;
const int middleSensorPin = A1;
const int rightSensorPin = A2;

// sensor thresholds
const int middleThreshold = 600;

int leftSensorPinValue;
int middleSensorPinValue;
int rightSensorPinValue;

//general power
int hPower = 250;
int lPower = 190; 

// functions decleration
void leftServo (int powerCase, int adjustDelay);
void rightServo (int powerCase, int adjustDelay);
void frontServo(void);
void stopMotor (void);
void mapValues(void);
void readValues(void);
void goForward(int power);
void goBackwards(int power);
void getSensorValues();

void setup()
{
  Serial.begin(9600);

  // setup pins motor
  pinMode(hEnablePin, OUTPUT);
  pinMode(controlMotorBack,OUTPUT);
  pinMode(controlMotorFront,OUTPUT);

  // setup pins sensors
  pinMode(leftSensorPin,INPUT);
  pinMode(middleSensorPin,INPUT);
  pinMode(rightSensorPin, INPUT);

  //setup pin servo
  backServo.attach(servoAnglePin);

  // activate something from inside 
  digitalWrite(leftSensorPin,HIGH);
  digitalWrite(middleSensorPin,HIGH);
  digitalWrite(rightSensorPin,HIGH);
}

void loop() 
{  

  getSensorValues();
  forwardServo();
  goForward(lPower);
  // lpower - 15
  
   if(middleSensorPinValue == 0 && leftSensorPinValue == 1 && rightSensorPinValue == 1) {
    forwardServo();
    goForward(lPower + 20);
  } else 
  
   if (middleSensorPinValue == 1 && leftSensorPinValue == 1 && rightSensorPinValue == 0) {
    rightServo(0, 100);
    goForward(lPower); 
   } else 
   
   if (middleSensorPinValue == 1 && leftSensorPinValue == 0 && rightSensorPinValue == 1) {
    leftServo(0, 100);
    goForward(lPower);
   }
//   } else if (middleSensorPinValue == 1 && leftSensorPinValue == 1 && rightSensorPinValue == 1) {
//    forwardServo();
//    stopMotor();
//    }
   
  
  
}

// function implementation
void readValues(bool showData) {
  leftSensorPinValue = analogRead(leftSensorPin);
  middleSensorPinValue = analogRead(middleSensorPin);
  rightSensorPinValue = analogRead(rightSensorPin);

  if(showData) {
    Serial.print("RightPin: ");
    Serial.println(rightSensorPinValue);

    Serial.print("MiddlePin: ");
    Serial.println(middleSensorPinValue);

    Serial.print("LeftPin: ");
    Serial.println(leftSensorPinValue);
    Serial.println("***********************************");
    delay(5000);
  }
}

void mapValues(bool showData) {
//  leftSensorPinValue /= 1023;
//  middleSensorPinValue /= 1023;
//  rightSensorPinValue /= 1023;

   if(leftSensorPinValue > middleThreshold)
    leftSensorPinValue = 1;
    else 
    leftSensorPinValue = 0;

   if(middleSensorPinValue > middleThreshold)
    middleSensorPinValue = 1;
    else 
    middleSensorPinValue = 0;

   if(rightSensorPinValue > middleThreshold)
    rightSensorPinValue = 1;
    else 
    rightSensorPinValue = 0;

  if(showData) {
    Serial.print("RightPinMapped: ");
    Serial.println(rightSensorPinValue);

    Serial.print("MiddlePinMapped: ");
    Serial.println(middleSensorPinValue);

    Serial.print("LeftPinMapped: ");
    Serial.println(leftSensorPinValue);
    Serial.println("***********************************");
    delay(2000);
  }
}

void getSensorValues() {
  readValues(false);
  mapValues(false);
}

void leftServo (int powerCase, int adjustDelay) {

  // 0 turbo
  // 1 normal

  switch(powerCase) {
      case 0:
        analogWrite(hEnablePin, hPower);
        delay(adjustDelay);
        backServo.write(rightAngle + 25);
        delay(adjustDelay);
        backServo.write(rightAngle + 15);
        delay(adjustDelay);
        backServo.write(rightAngle + 5);
        delay(adjustDelay);
        backServo.write(rightAngle);
        analogWrite(hEnablePin, hPower - 30);
        delay(adjustDelay);
        analogWrite(hEnablePin, lPower + 80);
        delay(adjustDelay);
        analogWrite(hEnablePin, lPower + 50);
        break;
     case 1:
        analogWrite(hEnablePin, hPower - 30);
        backServo.write(rightAngle);
        delay(adjustDelay + 100);
        analogWrite(hEnablePin, lPower);
        break;
    }
}

void rightServo (int powerCase, int adjustDelay) {
  // 0 turbo
  // 1 normal

  switch(powerCase) {
      case 0:
        analogWrite(hEnablePin, hPower + 100);
        delay(adjustDelay);
        backServo.write(leftAngle - 25);
        delay(adjustDelay);
        backServo.write(leftAngle - 15);
        delay(adjustDelay);
        backServo.write(leftAngle - 5);
        delay(adjustDelay);
        backServo.write(leftAngle);
        delay(adjustDelay);
        analogWrite(hEnablePin, lPower + 100);
        delay(adjustDelay);
        analogWrite(hEnablePin, lPower + 100);
        while(middleSensorPinValue == 1 && leftSensorPinValue == 1 && rightSensorPinValue == 0) { 
          getSensorValues();
        } 
        break;
     case 1:
        analogWrite(hEnablePin, hPower - 30);
        backServo.write(rightAngle);
        delay(adjustDelay + 100);
        analogWrite(hEnablePin, lPower);
        break;
    }
}

void forwardServo(void) {
  backServo.write(middleAngle);
}

void goForward(int power) {

  // forward polarity 
  digitalWrite(controlMotorFront, HIGH);
  digitalWrite(controlMotorBack, LOW);
  
  // zvac
  int i;
  analogWrite(hEnablePin,255);
  delay(4);

  // pwn
  for(i = 0; i < 3 ; i++) {
    if(i%2 == 0) { 
      analogWrite(hEnablePin, power);
      delay(10);
    }
    else { 
      analogWrite(hEnablePin, 0);
      delay(25);
  }
  
  getSensorValues();
  }
}

void goBackwards(int power) {
  analogWrite(hEnablePin, power);
  digitalWrite(controlMotorFront, LOW);
  digitalWrite(controlMotorBack, HIGH);
}

void stopMotor (void) {
  analogWrite(hEnablePin, 0);
}


