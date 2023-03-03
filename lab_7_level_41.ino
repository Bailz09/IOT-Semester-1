// C++ code
//
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
int buzzerPin=5;
int buttonPin=2;
int notesSBM[] = {392, 392, 440, 392, 349, 330, 294, 392, 392, 440, 392, 349, 330, 294, 392, 392, 392, 494, 392, 349, 330, 294, 262, 330, 330, 349, 294, 262, 294, 330, 294, 262, 262, 294, 330, 349, 392, 330, 294, 262, 392, 392, 440, 392, 349, 330, 294, 392, 392, 440, 392, 349, 330, 294, 392, 330, 294, 262, 294, 330, 294, 262, 262};
int durationsSBM[] = {250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 250, 250, 500, 250, 250, 500, 500, 250, 250, 500, 250, 250, 500, 500, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 250, 500, 500, 500, 500, 1000, 250, 500, 500, 500, 500, 1000};
int note;
int notesNOK[] = {262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523, 262, 294, 330, 392, 440, 494, 523};

int durationsNOK[] = {200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400, 200, 200, 200, 200, 400, 200, 400};
int notesRRR[] = {262, 262, 294, 294, 330, 330, 294, 262, 262, 294, 294, 330, 330, 294, 262, 262, 294, 294, 330, 330, 294, 262, 294, 262, 262, 262, 294, 294, 294, 330, 330, 330, 294, 294, 262, 262, 294, 294, 330, 330, 294};
int durationsRRR[] = {250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 500, 250};
int LED[] = {8, 9, 10, 11, 12, 13};
int count=0;
char input;
void setup ()
{
  Serial.begin(9600); //enables data to be sent to the serial monitor
  randomSeed(analogRead(0));
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(LED[0], OUTPUT); //sets the red LED as an output
  pinMode(LED[1], OUTPUT); //sets the red LED as an output
  pinMode(LED[2], OUTPUT); //sets the red LED as an output
  pinMode(LED[3], OUTPUT); //sets the red LED as an output
  pinMode(LED[4], OUTPUT); //sets the red LED as an output
  pinMode(LED[5], OUTPUT); //sets the red LED as an output  
}
void loop()
{  
  runMenu();
}
void NOK()
{
  for(int i=0;i<24;i++)
       {
     	 int myRandom = random(0, 6);
         note = notesNOK[i];   
         digitalWrite(LED[myRandom], HIGH);
         tone(buzzerPin, notesNOK[i], durationsNOK[i]);
         delay(durationsNOK[i]*1.3);
         digitalWrite(LED[myRandom], LOW);
         noTone(buzzerPin);
     if (digitalRead(buttonPin) == HIGH)
     {
       break;
     }
       }  
}
void SBM()
{
   for(int i=0;i<58;i++)
       {
     	 int myRandom = random(0, 6);
         note = notesSBM[i];   
         digitalWrite(LED[myRandom], HIGH);
         tone(buzzerPin, notesSBM[i], durationsSBM[i]);
         delay(durationsSBM[i]*1.3);
         digitalWrite(LED[myRandom], LOW);
         noTone(buzzerPin);
     if (digitalRead(buttonPin) == HIGH)
     {
       break;
     }
       }  
}
void RRR()
{
   for(int i = 0; i < sizeof(notesRRR)/sizeof(notesRRR[0]); i++)
       {
     	 int myRandom = random(0, 6);
         note = notesRRR[i];
         digitalWrite(LED[myRandom], HIGH);
         tone(buzzerPin, notesRRR[i], durationsRRR[i]); 
         delay(durationsRRR[i]*1.3);
         digitalWrite(LED[myRandom], LOW);
         noTone(buzzerPin);
     if (digitalRead(buttonPin) == HIGH)
     {
       break;
     }
       }  
}
void runMenu()
{
  Menu();
  if (count==1)
     {
       SBM(); 
     }
  else if (count==2)
  {
    RRR();
  }
  else if (count==3)
  {
    NOK();
  }
}
void Menu()
{
  Serial.println("Please Choose a Song You Would Like to Play");
  Serial.println("Press 'S' for Stand By Me, 'R' for Row Row Row your boat or 'N' for the nokia Ringtone");
  while(Serial.available()==0)
       {
       }
        input = Serial.read();
        Serial.println("Hit The Button to Stop playing and choose again");
        switch (input)
             {
          case 'S':
              {
                count=1;
                break;
              }
          case 'R':
              {
                count=2;
                break;
              }
          case 'N':
              {
                count=3;
                break;
              }
             }
                
       
}  
  