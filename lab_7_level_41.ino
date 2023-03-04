// Kevin Bailey (200544764@student.georgianc.on.ca)
// Friday March 3 2023
// Lab 7 Level 4 Musical Library

//define the library of musical notes
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
//declare variables
int buzzerPin=5;//The buzzerPin is connected to pin 5 of the Arduino.
int buttonPin=2;//The SW1 button is connected to pin 2 of the Arduino.
//for each song: putting the notes and duration of each note in two sepearate arrays
int notesSBM[] = {392, 392, 440, 392, 349, 330, 294, 392, 392, 440, 392, 349, 330, 294, 392, 392, 392, 494, 392, 349, 330, 294, 262, 330, 330, 349, 294, 262, 294, 330, 294, 262, 262, 294, 330, 349, 392, 330, 294, 262, 392, 392, 440, 392, 349, 330, 294, 392, 392, 440, 392, 349, 330, 294, 392, 330, 294, 262, 294, 330, 294, 262, 262};
int durationsSBM[] = {250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 250, 250, 500, 250, 250, 500, 500, 250, 250, 500, 250, 250, 500, 500, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 500, 500, 500, 500, 1000};
int notesNOK[] = {262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523};
int durationsNOK[] = {200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400};
int notesRRR[] = {262, 262, 294, 294, 330, 330, 294, 262, 262, 294, 294, 330, 330, 294, 262, 262, 294, 294, 330, 330, 294, 262, 294, 262, 262, 262, 294, 294, 294, 330, 330, 330, 294, 294, 262, 262, 294, 294, 330, 330, 294};
int durationsRRR[] = {250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250};
int LED[] = {8, 9, 10, 11, 12, 13};//an array for the pins of each LED connected to the arduino
int count=0;//a variable to keep track of which song is selected
char input;//a char variable to collect user input.
int note;//a variable to store the current musical note thats playing
void setup ()//The Setup function runs once
{
  Serial.begin(9600); //enables data to be sent to the serial monitor
  randomSeed(analogRead(0));//to make our random generator for the LEDs truly random
  pinMode(buzzerPin, OUTPUT);//setup buzzerPin as an output pin
  pinMode(buttonPin, INPUT);//setup buttonPin as an input pin
  pinMode(LED[0], OUTPUT); //sets the first LED in the array as an output
  pinMode(LED[1], OUTPUT); //sets the second LED in the array as an output
  pinMode(LED[2], OUTPUT); //sets the third LED in the array as an output
  pinMode(LED[3], OUTPUT); //sets the fourth LED in the array as an output
  pinMode(LED[4], OUTPUT); //sets the fifth LED in the array as an output
  pinMode(LED[5], OUTPUT); //sets the sixth LED in the array as an output
}
void loop()//The Loop function runs forever
{  
  runMenu();//a command to run the runMenu() function
}
void NOK()//a function that plays the Nokia Ringtone
{
  for(int i=0;i<24;i++)//sets the parameters for the i variable
       {
     	 int myRandom = random(0, 6);//creates a random number 0 to 5
         note = notesNOK[i];//stores the current note in the note variable   
         digitalWrite(LED[myRandom], HIGH);//turn on a random LED in the array
         tone(buzzerPin, notesNOK[i], durationsNOK[i]);//play the Nokia Ringtone by calling the notes and durations array 1 at a time respectively
         delay(durationsNOK[i]*1.3);//delay after each note and LED flash
         digitalWrite(LED[myRandom], LOW);//turn off the LED
     if (digitalRead(buttonPin) == HIGH)//checks if the button has been pressed
     {
       break;//exit the loop
     }
       }  
}
void SBM()//a function that plays Stand By Me
{
   for(int i=0;i<58;i++)//sets the parameters for the i variable
       {
     	 int myRandom = random(0, 6);//creates a random number 0 to 5
         note = notesSBM[i];//stores the current note in the note variable   
         digitalWrite(LED[myRandom], HIGH);//turn on a random LED in the array
         tone(buzzerPin, notesSBM[i], durationsSBM[i]);//play Stand By Me by calling the notes and durations array 1 at a time respectively
         delay(durationsSBM[i]*1.3);//delay after each note and LED flash
         digitalWrite(LED[myRandom], LOW);//turn off the LED
     if (digitalRead(buttonPin) == HIGH)//checks if the button has been pressed
     {
       break;//exit the loop
     }
       }  
}
void RRR()//a function that plays Row Row Row Your Boat
{
   for(int i = 0; i < sizeof(notesRRR)/sizeof(notesRRR[0]); i++)//sets the parameters for the i variable and array size(since ChatGPT didnt provide the Array size)
       {
     	 int myRandom = random(0, 6);//creates a random number 0 to 5
         note = notesRRR[i];//stores the current note in the note variable
         digitalWrite(LED[myRandom], HIGH);//turn on a random LED in the array
         tone(buzzerPin, notesRRR[i], durationsRRR[i]);//play Row Row Row Your Boat by calling the notes and durations array 1 at a time respectively 
         delay(durationsRRR[i]*1.3);//delay after each note and LED flash
         digitalWrite(LED[myRandom], LOW);//turn off the LED
     if (digitalRead(buttonPin) == HIGH)//checks if the button has been pressed
     {
       break;//exit the loop
     }
       }  
}
void runMenu()//a function that runs the main menu of the program
{
  Serial.println("Please Choose a Song You Would Like to Play");
  Serial.println("Press 'S' for Stand By Me, 'R' for Row Row Row your boat or 'N' for the nokia Ringtone");
  while(Serial.available()==0)//while nothing is entered
       {//do nothing
       }
        input = Serial.read();//gets input from the user
        Serial.println("Hit The Button to Stop playing and choose again");
        switch (input)//switch for the user input
             {
          case 'S'://if user enters 'S'
              {
                count=1;//set the count to 1
                break;//exits the switch
              }
          case 'R'://if user enters 'R'
              {
                count=2;//set the count to 2
                break;//exits the switch
              }
          case 'N'://if user enters 'N'
              {
                count=3;//set the count to 3
                break;//exits the switch
              }
             }      
  if (count==1)//if the count variable equals 1, play Stand by Me
     {
       Serial.println("Now Playing:");
       Serial.print("Stand By Me");
       Serial.println("");
       SBM(); 
     }
  else if (count==2)//if the count variable equals 2 play Row Row Row Your Boat
  {
    Serial.println("Now Playing:");
    Serial.print("Row Row Row Your Boat");
    Serial.println("");
    RRR();
  }
  else if (count==3)//if the count variable equals 3 play the Nokia Ringtone
  {
    Serial.println("Now Playing:");
    Serial.print("The Nokia Ringtone");
    Serial.println("");
    NOK();
  }
}

  