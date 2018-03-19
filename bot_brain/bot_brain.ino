const int hEnablePinRight = 9;
const int rightControlMotorBack = 8;
const int rightControlMotorFront = 7;

const int hEnablePinLeft = 3;
const int leftControlMotorBack = 4;
const int leftControlMotorFront = 2;

const int leftSensorOuterPin = A0;
const int leftSensorInnerPin = A1;
const int rightSensorOuterPin = A4;
const int rightSensorInnerPin = A3;

int leftSensorOuterPinValue;
int leftSensorInnerPinValue;
int rightSensorOuterPinValue;
int rightSensorInnerPinValue;

void LEFT (void);
void RIGHT (void);
void STOP (void);
void map_values(void);
void read_values(void);

void setup()
{
  pinMode(hEnablePinRight, OUTPUT);
  pinMode(hEnablePinLeft, OUTPUT);
  
  pinMode(rightControlMotorBack,OUTPUT);
  pinMode(rightControlMotorFront,OUTPUT);
  pinMode(leftControlMotorBack,OUTPUT);
  pinMode(leftControlMotorFront,OUTPUT);

  pinMode(leftSensorOuterPin,INPUT);
  pinMode(leftSensorInnerPin,INPUT);
  pinMode(rightSensorOuterPin, INPUT);
  pinMode(rightSensorInnerPin, INPUT);

  digitalWrite(leftSensorOuterPin,HIGH);
  digitalWrite(leftSensorInnerPin,HIGH);
  digitalWrite(rightSensorOuterPin,HIGH);
  digitalWrite(rightSensorInnerPin,HIGH);
  
  
}

void loop() 
{
 
digitalWrite(rightControlMotorFront,HIGH);
digitalWrite(rightControlMotorBack,LOW);
digitalWrite(leftControlMotorFront, HIGH);
digitalWrite(leftControlMotorBack,LOW);

while(1) {
  
  read_values();
  map_values();
  
  if(leftSensorOuterPinValue + leftSensorInnerPinValue >
     rightSensorOuterPinValue + rightSensorInnerPinValue) {
    RIGHT();
   } else if ( leftSensorOuterPinValue + leftSensorInnerPinValue <
     rightSensorOuterPinValue + rightSensorInnerPinValue) {
   LEFT();  
   }
}

}

void read_values() {
  leftSensorOuterPinValue = analogRead(leftSensorOuterPin);
  leftSensorInnerPinValue = analogRead(leftSensorInnerPin);
  rightSensorOuterPinValue = analogRead(rightSensorOuterPin);
  rightSensorInnerPinValue = analogRead(rightSensorInnerPin);
}

void map_values() {
  leftSensorOuterPinValue /= 1023;
  leftSensorInnerPinValue /= 1023;
  rightSensorOuterPinValue /= 1023;
  rightSensorInnerPinValue /= 1023;
}

void LEFT (void) {
   analogWrite(hEnablePinLeft, 30);
   digitalWrite(leftControlMotorBack,LOW);
   digitalWrite(leftControlMotorFront, HIGH);
   
   while(leftSensorOuterPinValue + leftSensorInnerPinValue <
     rightSensorOuterPinValue + rightSensorInnerPinValue)
   {
    digitalWrite(rightControlMotorFront, HIGH);
    digitalWrite(rightControlMotorBack,LOW); 

    read_values();
    map_values();
   }

   analogWrite(hEnablePinLeft, 255);
   digitalWrite(leftControlMotorFront,HIGH);
   digitalWrite(leftControlMotorBack,LOW);
}

void RIGHT (void) {
   analogWrite(hEnablePinRight, 30);
   digitalWrite(rightControlMotorBack,LOW);
   digitalWrite(rightControlMotorFront,HIGH);

   while(leftSensorOuterPinValue + leftSensorInnerPinValue >
     rightSensorOuterPinValue + rightSensorInnerPinValue)
   { 
    digitalWrite(leftControlMotorFront,HIGH);
    digitalWrite(leftControlMotorBack,LOW);

    read_values();
    map_values();
    }

   analogWrite(hEnablePinRight, 255);
   digitalWrite(rightControlMotorFront,HIGH);
   digitalWrite(rightControlMotorBack,LOW);
}

void STOP (void) {
analogWrite(rightControlMotorBack,0);
analogWrite(rightControlMotorFront,0);
analogWrite(leftControlMotorBack,0);
analogWrite(leftControlMotorFront,0);
}


