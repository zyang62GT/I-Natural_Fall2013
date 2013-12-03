     
#include <Servo.h>
// Flexiforce quick start example
// Reads A0 every 100ms and sends voltage value over serial
Servo myservo;
void setup() 
{
  // Start serial at 9600 baud
  
  myservo.attach(9);
  Serial.begin(9600);
}

    void loop() 
{
  // Read the input on analog pin 0:
  float sensorValue = analogRead(A0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue/700;
  Serial.println(voltage*90);
  myservo.write(voltage*90);
  // Print out the value you read:
  
  // Wait 100 milliseconds
  delay(100);
}
