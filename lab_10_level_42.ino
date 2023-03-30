// Kevin Bailey (200544764@student.georgianc.on.ca)
// Wednesday March 29 2023
// Lab 10 Level 4 Dual Arduino Motor

//declare variables
#include <Wire.h>//Include Wire library for I2C communication
#include <Servo.h>//Include Servo Library
Servo myservo;
int RGBRedpin = 9;//set pin 9 of arduino to the Red pin of the LED
int RGBBluepin = 10;//set pin 10 of arduino to the Blue pin of the LED
int RGBGreenpin = 11;//set pin 9 of arduino to the Green pin of the LED
int value = 0;//set value variable to zero
int count = 0;//set count variable to zero

void setup()//the setup function runs once
{
  myservo.attach(4);//attach servo to pin 4 of arduino
  pinMode(RGBRedpin, OUTPUT);//setup the Red pin of LED to an OUTPUT pin
  pinMode(RGBGreenpin, OUTPUT);//setup the Green pin of LED to an OUTPUT pin
  pinMode(RGBBluepin, OUTPUT);//setup the Blue pin of LED to an OUTPUT pin
  myservo.write(0);//set initial servo position to zero
  Wire.begin(1); //setup to receive from the input arduino         
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);//initialize serial monitor
}

void loop() //the loop function runs forever
{
  delay(500);//delay
  runProgram();//run the runProgram function
}
void receiveEvent(int howMany)//receive even function
{
  int newvalue = Wire.read();//read the value from input arduino    
  value = newvalue-1;//set value back to original value
  Serial.println(count);//print the count variable    
}
void runProgram()
{
  switch (value)//switch for the value variable 
  {
    case 0://when value is zero
    {
      count = 1;//set count variable to 1
      break;
    }
    case 1://and so on ...
    {
      count = 2;
      break;
    }
    case 2:
    {
      count = 3;
      break;
    }
    case 3:
    {
      count = 4;
      break;
    }
    case 4:
    {
      count = 5;
      break;
    }
    case 5:
    {
      count = 6;
      break;
    }
    case -1:
    {
      count = 7;
      break;
    }
  }
  if (count == 1)//if count variable is 1, run the red() function 
  {
    red();
  }
   else if (count == 2)//and so on.. 
   {
     green();
   }
   else if (count == 3)
   {
     blue();
   }
  else if (count == 4)
  {
    magenta();
  }
  else if (count == 5)
  {
    yellow();
  }
  else if (count == 6)//when servo tries to go passed the upper limit
  {
    count = 0;//reset the variables back to original values
    value = 0;
    magenta();//run each function on the way back to starting position
    blue();
    green();
    red();
  }
  else if (count == 7)//when servo tries to go below the lower limit 
  {
    count = 5;//set the variables to their max positions
    value = 4;
    green();//run each function on the way back to max position
    blue();
    magenta();
    yellow();
  }
}
void red()
{ 
  myservo.write(0);//servo position when colour is red
  analogWrite(RGBRedpin, 255);
  analogWrite(RGBGreenpin, 0);
  analogWrite(RGBBluepin, 0);
  delay(500);
}
void green()//and so on..
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
