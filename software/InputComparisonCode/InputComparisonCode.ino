#include <Servo.h>
Servo myservo1;
Servo myservo2;
int Motor1Control = 13;
int Motor2Control = 12;
int led4 = 4;
int led7 = 7;
int led8 = 8;
//int ResetButton = 2; //Not Used
int ServoVal;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led4, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
//  pinMode(ResetButton, INPUT); //Not in Use
  myservo1.attach(Motor1Control);
  myservo2.attach(Motor2Control);
}

const int MaxAngle = 70;
int Sensor1Max=0, Sensor2Max=0, servoVal=45;
float ratio=0.0;
int player1sum=0, player2sum=0;
// the loop routine runs over and over again forever:
void loop() {
  // Setup Loop
  for(int i=0 ; i<5 ; i++)
  {
      // reset the servos to Center
      myservo1.write(MaxAngle/2);
      myservo2.write(MaxAngle/2);
      
      Serial.print("Get Ready: "); Serial.println(i);
      // LEDs added to pins 4 7 8
      // Calibration can also be done here
      if(i > 4)
      {
          // All LEDs ON
          digitalWrite(led4, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, HIGH);
      }
      else if (i > 3)
      {
          // Two LEDs ON
          digitalWrite(led4, HIGH);
          digitalWrite(led7, HIGH);
          digitalWrite(led8, LOW);
      }
      else if (i > 2)
      {
          // One LED ON
          digitalWrite(led4, HIGH);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
      }
      else
      {
          // all LEDs OFF
          digitalWrite(led4, LOW);
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
      } 
      // Wait function 
      delay(1000);
    }
  
  // Game Loop
  for(int i=0 ; i<20 ; i++)
  {
    // read the input on analog pin 0:
    int sensorValue1 = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage1 = sensorValue1 * (5.0 / 1023.0);
    Serial.print("player 1 Sensor Value: "); Serial.println(sensorValue1);
    //Serial.print("player 1 voltage"); Serial.println(voltage1);
    
    int sensorValue2 = analogRead(A1);  
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage2 = sensorValue2 * (5.0 / 1023.0);
    Serial.print("player 2 Sensor Value: "); Serial.println(sensorValue2);
    //Serial.print("player 2 voltage"); Serial.println(voltage2);
    // print out the value you read:
    
    player1sum += sensorValue1;
    player2sum += sensorValue2;
    
    delay(500);
  }

  ratio = (float)player1sum/player2sum;
  Serial.print("\nRatio ");
  Serial.println(ratio);    
  if(ratio>1){
    //servoVal=179;
    Serial.print("player2 wins");
    while(1)
    {
        // Servo turns to 60 degrees
        // Pin 13 turns on
        ServoVal = MaxAngle-0;
        myservo1.write(MaxAngle-ServoVal);
        myservo2.write(ServoVal);
    }
  }
  else if(ratio<1){
    //servoVal=0;
    Serial.print("player1 wins.");
    while(1)
    {
        // Servo turns to 30 degrees
        // Pin 12 turns on
        ServoVal = 0;
        myservo1.write(MaxAngle-ServoVal);
        myservo2.write(ServoVal);
    }
  }
  else
  {
    Serial.print("Tie Game!!!");
    while(1)
    {
      ServoVal = MaxAngle/2;
      myservo1.write(ServoVal);
      myservo2.write(ServoVal);
    }
  }
  
  // Reset Variables
  player1sum = player2sum = 0;
  ServoVal = MaxAngle/2;
  myservo1.write(ServoVal);
  myservo2.write(ServoVal);
}
