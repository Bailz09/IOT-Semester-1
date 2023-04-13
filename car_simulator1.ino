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
#define BUZZER_PIN 9
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Servo rpmgauge;
int buttonPin = 6;
int buttonPin2 = 7;
int rotationPin = A0;
int rpm;
int gear = 1;
int data = 0;
int minRPM = 0;
int maxRPM = 8000;
int angle;
int previousRPM;
int carchoice = 0;
int trackchoice = 0;
String cars[] = { "Carrera GT", "Corvette ZR1", "GT-R NISMO" };
String tracks[] = { "Cayuga", "Calabogie", "Shannonville" };
float acceleration[] = { 3.5, 2.9, 2.7 };
int topspeed[] = { 205, 208, 195 };
int distance[] = { 1000, 1200, 800 };
int arraysizecars = sizeof(cars) / sizeof(cars[0]);
int arraysizetracks = sizeof(tracks) / sizeof(tracks[0]);
bool carselected = false;
bool trackselected = false;
bool firstpress = true;
bool secondpress = false;
String weather[]={"Sunny", "Rainy", "Snowy"};
String currentweather;
bool trackconditions = true;

unsigned long startMillis = 0;
float currentSpeed = 0.0; // mp/h
float currentPosition = 0.0; // meters
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousMillis = 0;


bool startmsg = true;
int gearspeed;
int currentrpm;

void setup()
{
    Serial.begin(9600);
    pinMode(rotationPin, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin, INPUT);
    rpmgauge.attach(8);
    rpmgauge.write(180);
    lcd.begin(16, 2);
    ring.begin();
    ring.show();
    pinMode(BUZZER_PIN, OUTPUT);
  	randomSeed(analogRead(A1));
    weathertoday();
}
void loop()
{
    while (startmsg)
    {
        startmsg = false;
        lcd.setCursor(0, 0);
        lcd.print("Press Button 1");
        lcd.setCursor(0, 1);
        lcd.print("To Cycle Cars");
        Serial.println("Welcome To Drag Race Ontario!!");
       
    }
    while (!carselected)
    {
        if (digitalRead(buttonPin) == HIGH)
        {
            if (firstpress)
            {
                Serial.println("Press button 2 to select a car choice");

            }
            firstpress = false;
            lcd.clear();
            carchoice = (carchoice + 1) % arraysizecars;
            carselection();
            delay(200);
        }
        if (digitalRead(buttonPin2) == HIGH)
        {
            carselected = true;
            secondpress = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Press Button 1");
            lcd.setCursor(0, 1);
            lcd.print("To Cycle Tracks");
        }
    }
    while (!trackselected)
    {
        if (digitalRead(buttonPin) == HIGH)
        {
            if (secondpress)
            {
                Serial.println("Press 's' to select track and start the race!");
            }
            secondpress = false;
            lcd.clear();
            trackchoice = (trackchoice + 1) % arraysizetracks;
            trackselection();
            delay(200);
        }
      while (trackconditions)
      {
        trackconditions=false;
        Serial.println("Todays Track Conditions Are: ");
        Serial.print(currentweather);
        Serial.println("");
      }
        if (Serial.read() == 's')
        {
            Serial.println("Use the potentiometer for throttle control");
            Serial.println("To up shift press 4 on the numpad and then enter");
            Serial.println("press 5 to down shift");
            startTime = millis();
            trackselected = true;
            lcd.clear();
        }
    }
    data = analogRead(rotationPin);
    if (gear % 2 == 0) // Even gear numbers
    {
        rpm = map(data, 0, 1023, maxRPM, minRPM);
        engine();
    }
    else // Odd gear numbers
    {
        rpm = map(data, 0, 1023, minRPM, maxRPM);
        engine();

    }
    gearspeed = topspeed[carchoice] / 6;
  	  
  if (currentweather == "Rainy")
  {
    gearspeed -= 2;
  }
  else if (currentweather == "Snowy")
  {
    maxRPM -=3;
  }
    currentSpeed = map(rpm, minRPM, maxRPM, gearspeed * (gear - 1), gearspeed * gear);
    
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
        int input = Serial.read();
        if (input == '4' && gear < 6)
        {
            gear++;
        }
        else if (input == '5' && gear > 1)
        {
            gear--;
        }
    }
    race();
    delay(25);
}

void updateservo()
{
    angle = map(rpm, minRPM, maxRPM, 180, 0);
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
    lcd.print(" mp/h");
}
void trackselection()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Track: ");
    lcd.print(tracks[trackchoice]);
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance[trackchoice]);
    lcd.print("M");
}
void race()
{
    unsigned long currentMillis = millis();
    elapsedTime = currentMillis - startTime;

    // Calculate speed in meters per second
    float speedInMetersPerSecond = (currentSpeed * 1000.0) / (60.0 * 60.0);
    currentPosition = speedInMetersPerSecond * (elapsedTime / 1000.0);

    if (currentPosition >= distance[trackchoice])
    {
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Finished!");
        lcd.setCursor(0, 1);
        lcd.print("Time: ");
        lcd.print(elapsedTime / 1000.0, 3);
        lcd.print("s");
        noTone(BUZZER_PIN);
        delay(5000);
        lcd.clear();
        ring.fill(ring.Color(0, 0, 0), 0, 16);
        ring.show();
        carselected = false;
        currentPosition = 0;
        currentSpeed = 0;
        startTime = 0;
        elapsedTime = 0;
        startMillis = millis();
        startmsg = true;
        firstpress = true;
        
        gear = 1;
        rpmgauge.write(180);
        trackselected=false;
        secondpress=true;
        trackconditions=true;
        weathertoday();
        carchoice=0;
        trackchoice=0;
        previousMillis = 0;
    }
}
void neo()
{
    // Calculate the percentage of RPM with respect to the min and max RPM
    int rpmPercentage = map(rpm, minRPM, maxRPM, 0, 100);

    // Calculate the number of LEDs to light up based on the RPM percentage
    int numLitLEDs = map(rpmPercentage, 0, 100, 0, 16);

    // Light up the LEDs backwards around the ring to simulate a tachometer
    for (int i = 15; i >= 0; i--)
    {
        if (i >= 15 - numLitLEDs)
        {
            if (i < 2)
            {
                ring.setPixelColor(i, ring.Color(255, 0, 0)); // Red

            }
            else if (i < 8)
            {
                ring.setPixelColor(i, ring.Color(255, 128, 0)); // Orange

            }
            else if (i < 12)
            {
                ring.setPixelColor(i, ring.Color(255, 255, 0)); // Yellow
            }
            else if (i < 15)
            {
                ring.setPixelColor(i, ring.Color(0, 255, 0)); // Green
            }
        }
        else
        {
            ring.setPixelColor(i, ring.Color(0, 0, 0)); // Off
        }
    }
    ring.show();
}

void engine()
{
    int frequency = map(rpm, minRPM, maxRPM, 100, 1000); // Map RPM to frequency (you can adjust the range as needed)
    tone(BUZZER_PIN, frequency);
}
void weathertoday()
{  
    randomSeed(analogRead(A1));
    int myrandom = random(0,3);
    currentweather=weather[myrandom];
    maxRPM = 8000;
    gearspeed = topspeed[carchoice]/6;

  
}






