#include <Servo.h>
Servo myservo1;
Servo myservo2;
const int Motor1Control = 12;
const int Motor2Control = 13;
float ratio=1.0;
float angle1 = 33.0;
float angle2 = 33.0;
void setup() {
    Serial.begin(9600);
    myservo1.attach(Motor1Control);
    myservo2.attach(Motor2Control);
}
float increment=0.0; 
void loop() { 
  
  int sensorValue1 = analogRead(A3);
  int sensorValue2 = analogRead(A4);
  //sensorValue2=sensorValue2*1000.0/23.0;
  ratio=float(sensorValue2)/sensorValue1;
  Serial.print("sensor1 = \n");
  Serial.println(sensorValue1);
  Serial.print("sensor2 = \n");
  Serial.println(sensorValue2);
  if(ratio > 6.0)
    ratio=6.0;
  if(ratio<1.0/6)
    ratio=1.0/6;
  Serial.print("ratio = \n");
  Serial.println(ratio);
  if(ratio>1)
  increment=1*(ratio-1);
  else if(ratio<=1)
    increment=1*(-1/ratio+1);
  Serial.print("increment = \n");
  Serial.println(increment);
  angle1=angle1+increment;
  myservo1.write(int(angle1));
  Serial.print("servo1 angle = \n");
  Serial.println(int(angle1));
  angle2=angle2-increment;
  myservo2.write(int(angle2));
  Serial.print("servo2 angle = \n");
  Serial.println(int(angle2));
  if(int(33+increment)>=66){
    while(1){
      Serial.print("Player1 wins.");
    }
  }
  else if (int(33+increment)<=0){
    while(1){
      Serial.print("Player2 wins.");
    }
  }
  //when one of the arms reached horizontal level and both arms were in contact
  delay(100);
}
