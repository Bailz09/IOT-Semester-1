// Kevin Bailey (200544764@student.georgianc.on.ca)
// Wednesday March 29 2023
// Lab 10 Level 4 Dual Arduino Motor

//declare variables
#include <Wire.h>//Include Wire library for I2C communication
int buttonPin = 2;// Define buttonPin as pin 2
int buttonPin2 = 3;// Define buttonPin2 as pin 3
int value = 0;//set value variable to zero

void setup()//the setup function runs once
{
  pinMode(buttonPin, INPUT);// Set buttonPin as input
  pinMode(buttonPin2, INPUT);// Set buttonPin2 as input
  Wire.begin();// Initialize I2C communication
  Serial.begin(9600);//initialize the serial monitor
}

void loop()//the loop runs forever 
{
  if (digitalRead(buttonPin) == HIGH)//check if button 1 is pressed
  {
    value++;//increase the value variable by 1
    delay(300);//delay
    int newvalue = value + 1;//store value as value +1 so that a negative number is not sent through to output arduino
	Serial.println(value);//print value to serial monitor
    Wire.beginTransmission(1);//transmit the new value to Arduino(1) 
    Wire.write(newvalue);      
    Wire.endTransmission(); //end transmission   
    delay(500);
  }
  if (digitalRead(buttonPin2) == HIGH)//check if button 2 is pressed
  {
    value--;//decrease the value variable by 1
    delay(300);//delay
    int newvalue = value + 1;//store value as value +1 so that a negative number is not sent through to output arduino
	Serial.println(value);//print value to serial monitor
    Wire.beginTransmission(1); //transmit the new value to Arduino(1) 
    Wire.write(newvalue);      
    Wire.endTransmission();//end transmission     
    delay(500);
  }
  if (value < 0)//resets the value variable if it goes outside the upper or lower limit
  {
    value = 4;
  }
   else if (value > 4) 
   {
     value = 0;
   } 
}
