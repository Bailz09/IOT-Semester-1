// Kevin Bailey (200544764@student.georgianc.on.ca)
// Tuesday March 14 2023
// Lab 8 Level 3 LCD choices

//declare variables
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 10// Change this to any available output pin
#define NUM_LEDS 16

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Servo rpmgauge;
int buttonPin=6;
int rotationPin = A0;
int rpm;
int gear = 1;
int data=0;
int minRPM=0;
int maxRPM=8000;
int angle;
int previousRPM;
int carchoice = 0;
String cars[]={"Carrera GT", "Corvette ZR1", "GT-R NISMO"} ; 
float acceleration[]={3.5, 2.9, 2.7};
int topspeed[]={205, 208, 195};    
int arraysize = sizeof(cars)/sizeof(cars[0]); 
bool carselected = false;
bool showmessage=true;
bool firstpress=true;
unsigned long startMillis = 0;
float distance = 1000.0; // meters
float currentSpeed = 0.0; // mp/h
float currentPosition = 0.0; // meters
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousMillis = 0;
bool raceStarted = false;
bool raceFinished = false;

int gearspeed;

void setup()
{
  Serial.begin(9600);
  pinMode(rotationPin,INPUT);
  pinMode(buttonPin, INPUT);
  rpmgauge.attach(8);
  rpmgauge.write(180);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Press Button");
  lcd.setCursor(0,1);
  lcd.print("To Cycle Choice");
  ring.begin();
  ring.show();
}
void loop()
{
   while (!carselected) 
  {
    if (digitalRead(buttonPin) == HIGH) 
    {
      if (firstpress && showmessage) 
      {
        Serial.println("Press 's' to select a car choice");
        showmessage = false;
      }
      firstpress = false;

      lcd.clear();
      carchoice = (carchoice + 1) % arraysize;
      carselection();
      delay(200);    
    }
    
    if (Serial.read() == 's') 
    {
      startTime = millis();
      carselected = true;
      lcd.clear();
    }
  }
 
  data = analogRead(rotationPin);
  if (gear % 2 == 0) // Even gear numbers
  { 
    rpm = map(data, 0, 1023, maxRPM, minRPM);
  } 
  else // Odd gear numbers
  { 
    rpm = map(data, 0, 1023, minRPM, maxRPM);
    
  }
  
	gearspeed = topspeed[carchoice]/6;
  	currentSpeed = map(rpm, minRPM, maxRPM, gearspeed * (gear -1), gearspeed * gear);
  	updateservo();
  if (rpm != previousRPM) 
  {
    status();
    previousRPM = rpm;
    neo();
  }
  
  updateservo();

  if (Serial.available() > 0) 
  {
    char input = Serial.read();
    if (input == 'u' && gear < 6) 
    {
      gear++;
    } 
    else if (input == 'd' && gear > 1) 
    {
      gear--;
    }
  }
    race();
delay(25);
 

}  
  
void updateservo()
 {
   angle=map(rpm, minRPM, maxRPM, 180, 0);
  rpmgauge.write(angle);
 }
void status()
{
   Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.println(" ");
  Serial.print("Gear: ");
  Serial.print(gear);
  Serial.println(" ");
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(currentSpeed);
  lcd.print(" mp/h");
}
void carselection()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Car: ");
  lcd.print(cars[carchoice]);

  lcd.setCursor(0, 1);
  lcd.print("Top Speed: ");
  lcd.print(topspeed[carchoice]);
  lcd.print(" km/h");
}

void race()
{
   unsigned long currentMillis = millis();
  elapsedTime = currentMillis - startTime;

  // Calculate speed in meters per second
  float speedInMetersPerSecond = (currentSpeed * 1000.0) / (60.0 * 60.0);
  currentPosition = speedInMetersPerSecond * (elapsedTime / 1000.0);
  
  if (currentPosition >= distance && !raceFinished)
  {
    raceFinished = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Finished!");
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(elapsedTime / 1000.0, 1);
    lcd.print("s");
    delay(5000);
    lcd.clear();
    ring.fill(ring.Color(0, 0, 0), 0, NUM_LEDS);
    ring.show();
    carselected = false;
    currentPosition = 0;
    startMillis = millis();
    showmessage = true;
    firstpress = true;
    raceFinished = false;
    gear=1;
  }
}
void neo() {
  // Calculate the percentage of RPM with respect to the min and max RPM
  int rpmPercentage = map(rpm, minRPM, maxRPM, 0, 100);

  // Calculate the number of LEDs to light up based on the RPM percentage
  int numLitLEDs = map(rpmPercentage, 0, 100, 0, 16);

  // Light up the LEDs backwards around the ring to simulate a tachometer
  for (int i = 15; i >=0; i--) {
    if (i >= 15 - numLitLEDs ) {
      if (i < 2) {
        ring.setPixelColor(i, ring.Color(255, 0, 0)); // Red
       
      } else if (i < 8) {
        ring.setPixelColor(i, ring.Color(255, 128, 0)); // Orange
       
      } else if (i < 12) {
         ring.setPixelColor(i, ring.Color(255, 255, 0)); // Yellow
      } else if (i<15) {
         ring.setPixelColor(i, ring.Color(0, 255, 0)); // Green
      }
    } else {
      ring.setPixelColor(i, ring.Color(0, 0, 0)); // Off
    }
  }

  
  ring.show();
}






  
    