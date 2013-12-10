#include<Servo.h>

Servo myservo;
Servo myservo2;
int MotorControl = 13;
int MotorControl2 = 12;

void setup()
{
  Serial.begin(9600);
  myservo.attach(MotorControl);
  myservo2.attach(MotorControl2);
}

int Pos=0;

void loop()
{
  myservo.write(0);
  myservo2.write(0);
  for(int i=0 ; i<13 ; i++)
  {
    Serial.println(Pos);
    Pos = i * 5;
    myservo.write(Pos);
    myservo2.write(Pos);
    delay(1000);
  }
}
