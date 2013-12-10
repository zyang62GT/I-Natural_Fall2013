#include <Servo.h>

/*******************************/
/****** Global Variables *******/
/*******************************/
Servo myservo1;
Servo myservo2;
const int Motor1Control = 13;
const int Motor2Control = 12;
// LED Pins
const int countdown1 = 11;  // Countdown
const int countdown2 = 10;  // Countdown
const int countdown3 = 9;  // Countdown
const int player1LED = 8;
const int player2LED = 7;

/*********************/
/******* Setup *******/
/*********************/
void setup() {
    Serial.begin(9600);
    
    // Setup servo Objects
    myservo1.attach(Motor1Control);
    myservo2.attach(Motor2Control);
    
    // Setup Countdown LEDs
    pinMode(countdown1, OUTPUT);
    pinMode(countdown2, OUTPUT);
    pinMode(countdown3, OUTPUT);
    
    // Setup Player LEDs
    pinMode(player1LED, OUTPUT);
    pinMode(player2LED, OUTPUT);
}

/*********************/
/***** Main Loop *****/
/*********************/
void loop()
{
  // Setup Variables
  float ratio = 1;
  int increment = 0, cycleCount = 0;
  const int MaxAngle = 72, WinCondition = 2;
  int angle = (MaxAngle/2)-1, playerWin=0;
  int sensorValue1=0, sensorValue2=0;
  boolean ledsON = false;
  
  { 
    // Servo Setup
    myservo1.write(angle);
    myservo2.write(angle);
    
    // Setup
    digitalWrite(player1LED, LOW);
    digitalWrite(player2LED, LOW);
    
    // Countdown
    Serial.println("Get Ready: 3");
    digitalWrite(countdown1, LOW);
    digitalWrite(countdown2, LOW);
    digitalWrite(countdown3, LOW);
    delay(1000);
    Serial.println("Get Ready: 2");
    digitalWrite(countdown1, LOW);
    digitalWrite(countdown2, LOW);
    digitalWrite(countdown3, HIGH);
    delay(1000);
    Serial.println("Get Ready: 1");
    digitalWrite(countdown1, LOW);
    digitalWrite(countdown2, HIGH);
    digitalWrite(countdown3, HIGH);
    delay(1000);
    Serial.println("Get Ready: 0");
    digitalWrite(countdown1, HIGH);
    digitalWrite(countdown2, HIGH);
    digitalWrite(countdown3, HIGH);
    delay(1000);
  }
  
  // GAME LOOP
  while(1)
  {
    // Read Analog Input
    sensorValue1 = analogRead(A3) + 1;
    sensorValue2 = analogRead(A4) + 1;
    
    // Find the ratio between the two inputs
    ratio = (float)sensorValue1/sensorValue2;
    Serial.print("Ratio: "); Serial.println(ratio);
    
    // Print Outputs
    //Serial.print("Sensor 1: "); Serial.println(sensorValue1);
    //Serial.print("Sensor 2: "); Serial.println(sensorValue2);    
    
    // Change the angle by who is winning
    if(ratio > 1) // Player 1
    {
      angle += 1;
      myservo1.write(angle);
      myservo2.write(MaxAngle-angle);
    }
    else if(ratio < 1) // Player 2
    {
      angle -= 1;
      myservo1.write(angle);
      myservo2.write(MaxAngle-angle);
    }
    else // tie. Neither Change
      ;
    
    // Win Condition
    // Send Print to Terminal for Debugging
    // Set Player LED High
    // Send break out of the game loop
    // Maybe add a counter to prevent an infinite game
    if(angle > (MaxAngle-WinCondition))
    { // Player 1 Wins
      Serial.print("Player 1 Wins");
      digitalWrite(player1LED, HIGH);
      digitalWrite(player2LED, LOW);
      playerWin = 1;
      break; 
    }
    else if(angle < (WinCondition))
    { // Player 2 Wins
      Serial.print("Player 2 Wins");
      digitalWrite(player1LED, LOW);
      digitalWrite(player2LED, HIGH);
      playerWin = 2;
      break; 
    }
    
    if(cycleCount > 2)
    {
      if(ledsON)
      {
        digitalWrite(player1LED, LOW);
        digitalWrite(player2LED, LOW);
      }
      else
      {
        digitalWrite(player1LED, HIGH);
        digitalWrite(player2LED, HIGH);
      }
      ledsON = !ledsON;
      cycleCount = 0;
    }
    else
    {
      cycleCount++;
    }
    //Serial.print("Cycle Count: "); Serial.println(cycleCount);
    
    // Delay for a fifth of a second to prevent 
    // too short of a game.
    delay(200);
  }
  
  while(1)
  {
    ; // Wait at end game until signal to restart
  }
}
