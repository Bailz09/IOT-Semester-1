//Kevin Bailey 200544764
//Lab 10 Level 3

#include <Servo.h>
Servo myservo;

int RGBRedpin = 9; //The red RGB LED is connected pin 9 of the Arduino.
int RGBBluepin = 10; //The blue RGB LED is connected pin 11 of the Arduino.
int RGBGreenpin = 11; //The green RGB LED is connected pin 10 of the Arduino.
int buttonPin = 2;
int buttonPin2 = 3;
int value=0;
int count=0;
void setup()
{
  myservo.attach(4);
  pinMode(buttonPin, INPUT);
  pinMode(RGBRedpin, OUTPUT); //Setup red RGB LED pin as an output pin.
  pinMode(RGBGreenpin, OUTPUT); //Setup green RGB LED pin as an output pin.
  pinMode(RGBBluepin, OUTPUT); //Setup blue RGB LED pin as an output pin.
  pinMode(buttonPin2, INPUT);
  myservo.write(0);
  Serial.begin(9600);
}
void loop()
{     
  runProgram();		
}
void runProgram()
{
    if(digitalRead(buttonPin)==HIGH)
  {
    value++;
    delay(300);
    Serial.println(value);
  }
  if (digitalRead(buttonPin2)==HIGH)
      {
        value--;
        delay(300);
        Serial.println(value);
      }
      switch (value)
      {
        case 0:
        {
          count=1;
          break;
        }
        case 1:
        {
          count=2;
          break;
        }
        case 2:
        {
          count=3;
          break;
        }
        case 3:
        {
          count=4;
          break;
        }
        case 4:
        {
          count=5;
          break;
        }
        case 5:
        {
          count=6;
          break;
        }
        case -1:
        {
          count=7;
          break;
        }
      }
  if (count ==1)
  {   
    red();	
  }
  else if (count==2)
  {  
    green();	
  }
  else if (count==3)
  { 
    blue();
  }
  else if (count==4)
  {
    magenta(); 	
  }
  else if (count==5)
  {  
    yellow();	
  }
  else if (count==6)
  {
    count=0;
    value=0;
    magenta();
    blue();
    green();
    red();
  }
  else if (count ==7)
  {
    count = 5;
    value = 4;
    green();
    blue();
    magenta();
  }
}
void red()
{
  myservo.write(0);
  analogWrite(RGBRedpin, 255);
  analogWrite(RGBGreenpin, 0);
  analogWrite(RGBBluepin, 0);
  delay(500);
}
void green()
{
  myservo.write(45);
  analogWrite(RGBRedpin, 0);
  analogWrite(RGBGreenpin, 255);
  analogWrite(RGBBluepin, 0);
  delay(500);
}
void blue()
{
  myservo.write(90);
  analogWrite(RGBRedpin, 0);
  analogWrite(RGBGreenpin, 0);
  analogWrite(RGBBluepin, 255);
  delay(500);
}
void magenta()
{
  myservo.write(135);
  analogWrite(RGBRedpin, 255);
  analogWrite(RGBGreenpin, 0);
  analogWrite(RGBBluepin, 255);
  delay(500);
}
void yellow()
{
  myservo.write(180);
  analogWrite(RGBRedpin, 255);
  analogWrite(RGBGreenpin, 255);
  analogWrite(RGBBluepin, 0);
  delay(500);
}