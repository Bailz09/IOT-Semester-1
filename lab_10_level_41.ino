#include <Wire.h>

int buttonPin = 2;
int buttonPin2 = 3;
int value = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);

  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    value++;
    delay(300);
    
     int newvalue = value + 1;
Serial.println(value);
  Wire.beginTransmission(1); 
  Wire.write(newvalue);      
  Wire.endTransmission();    

  delay(500);
  }
  if (digitalRead(buttonPin2) == HIGH) {
    value--;
    delay(300);
    
    int newvalue = value + 1;
Serial.println(value);
  Wire.beginTransmission(1); 
  Wire.write(newvalue);      
  Wire.endTransmission();    

  delay(500);
  }

  if (value < 0) {
    value = 4;
  } else if (value > 4) {
    value = 0;
  }

 
}
