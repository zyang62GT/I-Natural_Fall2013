#include <Servo.h>
Servo myservo1;
Servo myservo2;
const int Motor1Control = 13;
const int Motor2Control = 12;

// LED Pins
int led4 = 4;
int led7 = 7;
int led8 = 8;

float ratio=0.0;
void setup() {
    Serial.begin(9600);
    myservo1.attach(Motor1Control);
    myservo2.attach(Motor2Control);
}
float increment=0.0;

    
void loop() { 
    for(int i=0 ; i<5 ; i++)
  {
      // LEDs added to pins 4 7 8
      // Calibration can also be done here
      if(i > 4)
      {
          // All LEDs OFF
          digitalWrite(led4, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
      }
      else if (i > 3)
      {
          // Two LEDs off
          digitalWrite(led4, LOW);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
      }
      else if (i > 2)
      {
          // One LED off
          digitalWrite(led4, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, HIGH);
      }
      else
      {
          // all LEDs on
          digitalWrite(led4, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
      } 
      // Wait function 
      delay(1000);
    }
    
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);

  ratio=float(sensorValue2)/sensorValue1;
  Serial.print("Ratio: "); Serial.println(ratio);

  if(ratio > 6.0){
    ratio=6.0;
  }if(ratio<1.0/6){
    ratio=1.0/6;
  }if(ratio>1){
  increment=6.5*(ratio-1);
  }else if(ratio<=1){
    increment=6.5*(-1/ratio+1);
  }

  myservo1.write(int(32.5+increment));
  myservo2.write(75-int(32.5+increment));

  
  // Algorithm to check if one of the players won
  if(int(32.5+increment)>=75){
    while(1){
      Serial.print("Player1 wins.");
    }
  }
  else if (int(32.5+increment)<=0){
    while(1){
      Serial.print("Player2 wins.");
    }
  }
  //when one of the arms reached horizontal level and both arms were in contact
  delay(100);
}



