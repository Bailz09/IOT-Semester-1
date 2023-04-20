// Kevin Bailey (200544764@student.georgianc.on.ca)
// Thursday April 20 2023
// Final Project - Car Simulator 

//declare variables and libraries
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
String cars[] = { "Carrera GT", "Corvette ZR1", "GT-R NISMO", "Bugatti Veyron", "Bugatti Chiron" };
String tracks[] = { "Cayuga", "Calabogie", "Shannonville", "Sunset", "Grand Bend" };
float acceleration[] = { 3.5, 2.9, 2.7, 2.5, 2.3 };
int topspeed[] = { 205, 208, 195, 270, 304 };
int distance[] = { 1000, 1200, 800, 600, 2000 };
int arraysizecars = sizeof(cars) / sizeof(cars[0]);
int arraysizetracks = sizeof(tracks) / sizeof(tracks[0]);
bool carselected = false;
bool trackselected = false;
bool firstpress = true;
bool secondpress = false;
String weather[]={"Sunny", "Rainy", "Snowy"};
String currentweather;
bool trackconditions = true;
bool startmsg = true;
int gearspeed;
int currentrpm;
int input;
int newgearspeed;
int newmaxRPM;
//variables that chat gpt provided me for my race clock timer
unsigned long startMillis = 0;
float currentSpeed = 0.0; // mp/h
float currentPosition = 0.0; // meters
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousMillis = 0;

void setup()//setup function runs once
{
    Serial.begin(9600);//initialized the serial monitor
    pinMode(rotationPin, INPUT);//set the inputs
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin, INPUT);
    rpmgauge.attach(8);//sets the servo to pin 8
    rpmgauge.write(180);//sets the servo start position
    lcd.begin(16, 2);//sets up the lcd monitor
    ring.begin();//setup for the lcd ring
    ring.show();
    pinMode(BUZZER_PIN, OUTPUT);//set the buzzer pin to an output pin
  	randomSeed(analogRead(A1));//makes the random weather function truly random
    weathertoday();//run the weather function
//so i had a little bit of trouble getting the weather to display before the race started
//and to have the weather affect the conditions of the actual race, chat gpt suggested that
//I try putting the weather function in the setup, and you will see later on that to get new 
//conditions for everyrace, i again ran the weather function at the end of the race
}
void loop()
{
   runSim();//a single function that runs the whole program 
}
void welcome()
{
  while (startmsg)//a while loop to display the start message
    {
        startmsg = false;
        lcd.setCursor(0, 0);
        lcd.print("Press Button 1");
        lcd.setCursor(0, 1);
        lcd.print("To Cycle Cars");
        Serial.println("Welcome To Drag Race Ontario!!");     
    }
    while (!carselected)//a while loop for the car selection
    {
        if (digitalRead(buttonPin) == HIGH)//check for button press
        {
            if (firstpress)//a boolean for the car selection message
            {
                Serial.println("Press button 2 to select a car choice");
            }
            firstpress = false;
            lcd.clear();
            carchoice = (carchoice + 1) % arraysizecars;//cycles through the cars array with every button push
            carselection();//a function for displaying the car choices
            delay(200);
        }
        if (digitalRead(buttonPin2) == HIGH)//checks if button 2 has been pushed
        {
            carselected = true;//sets the carselected boolean to true effectively exiting the carselected while loop
            secondpress = true;//a boolean for displaying a message after a car is selected
            lcd.clear();//a message on the lcd screen
            lcd.setCursor(0, 0);
            lcd.print("Press Button 1");
            lcd.setCursor(0, 1);
            lcd.print("To Cycle Tracks");
        }
    }
    while (!trackselected)//a while loop for the track selection process
    {
        if (digitalRead(buttonPin) == HIGH)//checks if button 1 is pushed
        {
            if (secondpress)//a boolean for the track selection message
            {
                Serial.println("Press 's' to select track and start the race!");
            }
            secondpress = false;//set to false so the message doesnt spam the serial monitor
            lcd.clear();
            trackchoice = (trackchoice + 1) % arraysizetracks;//just like above the tracks will cycle with the button 1 pushes
            trackselection();//a function for displaying the track selections
            delay(200);
        }
      while (trackconditions)//a while loop for displaying the weather conditions
      {
        trackconditions=false;//again set to false so the weather conditions are displayed once
        Serial.println("Todays Track Conditions Are: ");
        Serial.print(currentweather);
        Serial.println("");
      }
        if (Serial.read() == 's')//if 's' is entered..
        {
            Serial.println("Use the potentiometer for throttle control");
            Serial.println("To up shift press 4 on the numpad and then enter");
            Serial.println("press 5 to down shift");
            startTime = millis();//starts the race clock
            trackselected = true;//sets trackselected boolean to true
            lcd.clear();
        }
    }
}
void updateservo()//a function for updating the servo
{
    angle = map(rpm, minRPM, maxRPM, 180, 0);//maps the servo motor to move within the rpm range
    rpmgauge.write(angle);
}
void status()//a function for displaying the cars current speed, RPM, and gear number
{
    Serial.print("RPM: ");
    Serial.print(rpm);
    Serial.println(" ");
    Serial.print("Gear: ");
    Serial.print(gear);
    Serial.println(" ");
    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.print(currentSpeed);
    lcd.print("mp/h");
}
void carselection()//a function for displaying the car menu
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Car: ");
    lcd.print(cars[carchoice]);//displays from the cars array
    lcd.setCursor(0, 1);
    lcd.print("TopSpeed:");
    lcd.print(topspeed[carchoice]);//displays from the topspeed array
    lcd.print("mp/h");
}
void trackselection()//a function for displaing the track menu
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Track: ");
    lcd.print(tracks[trackchoice]);//displays from tracks array
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance[trackchoice]);//displays from distance array
    lcd.print("M");
}
void race()
{
    data = analogRead(rotationPin);//sets the data variable to the potentiometer value
    if (gear % 2 == 0) // Even gear numbers the dial runs in the oppposite direction
    {
        rpm = map(data, 0, 1023, maxRPM, minRPM);//maps the data value to the range of the RPM (8000-0)
        engine();//a function for the piezo buzzer to simulate RPM rising and falling
    }
    else // Odd gear numbers the dial runs in the norml direction
    {
        rpm = map(data, 0, 1023, minRPM, maxRPM);//maps the data value to the range of the RPM (0-8000)
        engine();//a function for the piezo buzzer to simulate RPM rising and falling

    }
      gearspeed = topspeed[carchoice] / 6;//sets a top speed for each gear (topspeed/6 gears)
  	  newgearspeed=gearspeed;//a new gearspeed variable for updating when weather conditions change
 
  if (currentweather == "Rainy")//if the weather is rainy
  {
    newgearspeed -= 2;//drop 2 mph off each gear
  }
  else if (currentweather == "Snowy")//if the weather is snowy
  {
    newgearspeed -=3;//drop 3mph off each gear
  }
  //maps the current speed based on the current rpm within the min and max range, min speed is gearspeed * gear -1 because the car starts in the first gear and not gear 0
    currentSpeed = map(rpm, minRPM, maxRPM, newgearspeed * (gear - 1), newgearspeed * gear);
    
    updateservo();//a function for updating the servo position(which just maps the cars current rpm to the position on the servo)
    if (rpm != previousRPM)//an if statement for updating the speed and rpm anytime the rpm value changes
    {
        status();//a function for displaying the current speed and rpm
        previousRPM = rpm;//stores current rpm value into previousrpm variable
        neo();//a function for the NEO pixel Ring (check comments under that function)
    }
    updateservo();//i put this in again because the servo was lagging behing quite a bit and possibly needed to be updated more often, this seemed to help, i hadto play around with putting it in different spots alot

    if (Serial.available() > 0)//checks if there is any data from the serial monitor
    {
        input = Serial.read();//sets the input variable to what ever is entered in the serial monitor
      //originally i had the gear shift up and down set to 'u' and 'd' but because you have to push enter i chose something closer to the enter key
        if (input == '4' && gear < 6)//if current gear is less than 6 and 4 is entered in the serial monitor
        {
            gear++;//then the gear increases by 1
        }
        else if (input == '5' && gear > 1)//if current gear is greater than 1 and 5 is entered in the serial monitor
        {
            gear--;//then gear decreases by 1
        }
    }
  
  	chatGPT();

    if (currentPosition >= distance[trackchoice])//if the current car position is greater than the tracks distance then the race ends
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Finished!");
        lcd.setCursor(0, 1);
        lcd.print("Time: ");
        lcd.print(elapsedTime / 1000.0, 3);//displays how long it took to display the race to 3 decimal places
        lcd.print("s");
        noTone(BUZZER_PIN);//shuts the piezo buzzer off
        delay(5000);//5 second delay to view results
      //and then everything resets back to default values to start the program over again
        lcd.clear();
        ring.fill(ring.Color(0, 0, 0), 0, 16);
        ring.show();
        carselected = false;
        currentPosition = 0;
        currentSpeed = 0;
        startTime = 0;
        elapsedTime = 0;
        startmsg = true;
        firstpress = true;
        gear = 1;
        rpmgauge.write(180);
        trackselected=false;
        secondpress=true;
        trackconditions=true;
        weathertoday();//run the weather function for a new weather condition for the next race
    }
}
void chatGPT()
{
  //ok so this part of my code i had chatGPT help me with as i could not grasp the timer aspect or how to implement it without the help of chatGPT
    unsigned long currentMillis = millis();//from what i gather it assigns the current time on the program run clock to when you press 's' and enter on the serial monitor starting the race
    elapsedTime = currentMillis - startTime;//and essentially starting the race clock

    // Calculate speed in meters per second
    float speedInMetersPerSecond = (currentSpeed * 1000.0) / (60.0 * 60.0);//a calculation for determining the speed
    currentPosition = speedInMetersPerSecond * (elapsedTime / 1000.0);
}
  
void neo()
{
    //Map the percentage of RPM with respect to the min and max RPM
    int rpmPercentage = map(rpm, minRPM, maxRPM, 0, 100);

    //Map the number of LEDs to light up based on the RPM percentage
    int numLitLEDs = map(rpmPercentage, 0, 100, 0, 16);//0-16 because there is 16 leds
 
    // Light up the LEDs backwards around the ring to simulate a tachometer
    for (int i = 15; i >= 0; i--)//i set it to 15 so one led remains off at the end of the ring
    {
        if (i >= 15 - numLitLEDs)
        {
            if (i < 2)//if the last two leds are lit, light them red
            {
                ring.setPixelColor(i, ring.Color(255, 0, 0)); // Red

            }
            else if (i < 8)//between 8 and 12 light orange
            {
                ring.setPixelColor(i, ring.Color(255, 128, 0)); // Orange

            }
            else if (i < 12)//between 12 and 15 light yellow
            {
                ring.setPixelColor(i, ring.Color(255, 255, 0)); // Yellow
            }
            else if (i < 15)//between 15 and 12 light green
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
    int frequency = map(rpm, minRPM, maxRPM, 100, 500); // Map RPM to frequency (you can adjust the range as needed)
    tone(BUZZER_PIN, frequency);
}
void weathertoday()
{  
    //randomSeed(analogRead(A1));//makes the random function truly random, i put this in again because it seemed like the random generator wasnt working properly and this seemed to fix it
    int myrandom = random(0,3);//random generator between 0 and 2
    currentweather=weather[myrandom];//sets the current weather to a random index number in the array
   //the max RPM and gearspeed calculations are in here because the weather wasnt affecting the cars performace without it (needed updating)
    maxRPM = 8000;
    gearspeed = topspeed[carchoice]/6; 
}
void runSim()//a function for the main loop
{
  welcome();
  race();
  delay(25);
}





