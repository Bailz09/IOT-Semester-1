#include <Wire.h>
#include <Servo.h>

Servo myservo;

int RGBRedpin = 9;
int RGBBluepin = 10;
int RGBGreenpin = 11;
int value = 0;
int count = 0;

void setup() {
  myservo.attach(4);
  pinMode(RGBRedpin, OUTPUT);
  pinMode(RGBGreenpin, OUTPUT);
  pinMode(RGBBluepin, OUTPUT);
  myservo.write(0);

  Wire.begin(1);          
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(500);
  runProgram();
}

void receiveEvent(int howMany)


  {
  int newvalue = Wire.read();    
  value = newvalue-1;
  Serial.println(count);  
  
  
}



void runProgram() {

  switch (value) {
    case 0:
      count = 1;
      break;
    case 1:
      count = 2;
      break;
    case 2:
      count = 3;
      break;
    case 3:
      count = 4;
      break;
    case 4:
      count = 5;
      break;
    case 5:
      count = 6;
      break;
    case -1:
      count = 7;
      break;
  }

  if (count == 1) {
    red();
  } else if (count == 2) {
    green();
  } else if (count == 3) {
    blue();
  } else if (count == 4) {
    magenta();
  } else if (count == 5) {
    yellow();
  } else if (count == 6) {
    count = 0;
    value = 0;
    magenta();
    blue();
    green();
    red();
    Serial.println("value is");
    Serial.print(value);
    Serial.println("count is");
    Serial.print(count);
  } else if (count == 7) {
    count = 5;
    value = 4;
    green();
    blue();
    magenta();
    yellow();
    Serial.println("value is");
    Serial.print(value);
    Serial.println("count is");
    Serial.print(count);
    
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
