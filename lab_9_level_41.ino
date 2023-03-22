// Kevin Bailey (200544764@student.georgianc.on.ca)
// Wednesday March 22 2023
// Lab 9 Level 4 IR Remote Custom

//declare variables
#include <IRremote.h>
#define IR_RECEIVE_PIN 11
#define btn1 16
#define btn2 17
#define btn3 18
#define btn4 20
#define btn5 21
#define btn6 22
#define btn7 24
#define btn8 25
#define btn9 26
#define powerbtn 0
int value;
int LED[]={5, 6, 7, 8, 9, 10};
int LEDleft[]={8, 9, 10};
int LEDright[]={5, 6, 7};
bool lightshow=false;
int count=0;
int buttonPin=2;
void setup()//the setup function runs once
{
  Serial.begin(9600);//initialize the serial monitor
  IrReceiver.begin(IR_RECEIVE_PIN);//initialize the IR remote
  pinMode(LED[0, 1, 2, 3, 4, 5], OUTPUT);//set the LED pins to output pins
  pinMode(buttonPin, INPUT);//setup the buttonPin as an input
  randomSeed(analogRead(0));//make the random generators actually random
  Serial.println("Welcome please hit power button to continue");//welcome message
}
void loop()//the loop function runs forever 
{
  runMenu();//runMenu function
}
void runMenu()
{
  if (IrReceiver.decode()) //detects signal from IR remote
  {
    IrReceiver.resume();//keep listening for other IR remote signals
    value = IrReceiver.decodedIRData.command;//stores the decoded signal from the remote as the value variable
     if (value==powerbtn)//If power button is pushed
     {
       lightshow=false;//set the lightshow boolean to false
       start();//run the start function  
     }
   
	else if (value==btn1)//then if btn1 is pushed
    {
      lightshowmenu();// run the lightshowmenu function  
    } 
     while (lightshow && count==1)//while lightshow boolean is true
     {
       if (IrReceiver.decode())//detects signal from IR remote 
       {
         IrReceiver.resume();//keep listening for other IR remote signals
         value = IrReceiver.decodedIRData.command;//stores the decoded signal from the remote as the value variable
         if (value==powerbtn)//if powerbtn is pushed return to the main menu
         {
           lightshow=false;
           start();
           break;
         }
         else if (value==btn7)//if btn7
         {
           Serial.println("Hit the Pushbutton to Stop the LightShow");
           Serial.println("And return to the LightShow menu");
           left();//run the left function
         }
         else if (value==btn8)//if btn8
         {
           Serial.println("Hit the Pushbutton to Stop the LightShow");
           Serial.println("And return to the LightShow menu");
           right();//run the right function
         }
         else if (value==btn9)//if btn9
         {
           Serial.println("Hit the Pushbutton to Stop the LightShow");
           Serial.println("And return to the LightShow menu");
           all();//run the all function
         }                   
       }
   }
  }
}
void start()//function for the main menu
{
  count = 1;
  Serial.println("");
  Serial.println("");
  Serial.println("Please hit button 1 on the IR Remote");
  Serial.println("to access the lightshow Menu");
}
void lightshowmenu()//function for lightshow sub menu
{
  Serial.println("");
  Serial.println("");
  Serial.println("Press 7 for left side light show");
  Serial.println("Press 8 for right side light show");
  Serial.println("Press 9 for all light lightshow");
  Serial.println("");
  Serial.println("");
  lightshow=true;
}
void left()//function for the left side light show
{
  for(int i=0;i<25;i++)//loop runs 25 times
           {
             int myrandomleft = random(0,3);//random generator for LED lights
             digitalWrite(LEDleft[myrandomleft], HIGH);
             int randomdelayleft = random(0, 6);//random generator for delay times
             delay(randomdelayleft*250);
             digitalWrite(LEDleft[myrandomleft], LOW);   
                if (digitalRead(buttonPin) == HIGH )//checks if the button has been pressed
                  {
                    lightshowmenu();//return to the menu
                    break;//exit the loop
                  }
           }
  lightshowmenu();//return to menu after lightshow has commenced
}
void right()//function for the right side lightshow
{
  for (int i=0;i<25;i++)
           {
             int myrandomright = random(0,3);//random generator for LED lights
             digitalWrite(LEDright[myrandomright], HIGH);
             int randomdelayright = random(0, 6);//random generator for delay times       
             delay(randomdelayright*250);
             digitalWrite(LEDright[myrandomright], LOW);
             	if (digitalRead(buttonPin) == HIGH)//checks if the button has been pressed
                {
                  lightshowmenu();//back to menu
                  break;//exit the loop
                }
           }
  lightshowmenu();
}
void all()
{
  for (int i=0;i<25;i++)
           {
             int myrandomall = random(0,6);
             digitalWrite(LED[myrandomall], HIGH);
             int randomdelayall = random(0, 6);       
             delay(randomdelayall*250);
             digitalWrite(LED[myrandomall], LOW);
               if (digitalRead(buttonPin) == HIGH)//checks if the button has been pressed
               {
                 lightshowmenu();
                 break;//exit the loop
               }
           }
  lightshowmenu();
}
