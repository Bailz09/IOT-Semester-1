// Kevin Bailey (200544764@student.georgianc.on.ca)
// Sunday March 19 2023
// Lab 9 Level 3 IR Remote

//declare variables
#include <IRremote.h>
#define IR_RECEIVE_PIN 11
#define btn1 16
#define btn2 17
#define btn3 18
#define btn4 20
#define btn5 21
#define btn6 22
#define powerbtn 0
int value;
int redLED=8;
int blueLED=7;
bool power=true;
bool blueON=false;
bool redON=false;
bool bluemenu=false;
bool redmenu=false;
bool bothmenu=false;
bool goodbye=false;
int count=0;

void setup()//the setup function runs once
{
  Serial.begin(9600);//initialize the serial monitor
  IrReceiver.begin(IR_RECEIVE_PIN);//initialize the IR remote
  pinMode(redLED, OUTPUT);//setup the redLED pin as an output pin
  pinMode(blueLED, OUTPUT);//setup the blueLED pin as an output pin
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
       start();//run the start function
     }
	if (value==btn1)//then if btn1 is pushed
    {
      bluemenus();// run the bluemenus function  
    }
       else if (value==btn2)//or if btn2
       {
         redmenus();//redmenus function
       }
       else if (value==btn3)//or if btn3
       {
         bothmenus();//bothmenus function
       }
     while (bluemenu && count==1)//while bluemenu boolean is true
     {
       if (IrReceiver.decode())//detects signal from IR remote 
       {
         IrReceiver.resume();//keep listening for other IR remote signals
         value = IrReceiver.decodedIRData.command;//stores the decoded signal from the remote as the value variable
       	if(value==btn4)//if btn4 is pushed
       	{
          controlblue();//control blue LED
        }
         else if (value==btn5)//or btn5
         {
           redmenus();//go to redmenus  
         }
         else if (value==btn6)//or btn6
         {
           bothmenus();//go to bothmenus
         }
         else if (value==powerbtn)//or if powerbtn
         {
           count=2;//set count variable to 2(print goodbye message)
         }
       }
   }
   while (redmenu && count ==1)//while the redmenu boolean is true
     {
       if (IrReceiver.decode()) 
       {
         IrReceiver.resume();
         value = IrReceiver.decodedIRData.command;
       	if(value==btn4)//if btn4
       	{
          controlred();//control the red LED
        }
         else if (value==btn5)//or if btn5
         {
           bluemenus();//go to bluemenus
         }
         else if (value==btn6)//or if btn6
         {
           bothmenus();//go to bothmenus
         }
          else if (value==powerbtn)//or if powerbtn
         {
           count=2;//print goodbye
         }
  }
}
   while (bothmenu && count ==1)//while the bothmenu boolean is true
     {
       if (IrReceiver.decode()) 
       {
         IrReceiver.resume();
         value = IrReceiver.decodedIRData.command;
       	if(value==btn4)//if btn 4
       	{
          controlboth();//control both LEDS
        }
         else if (value==btn5)//or btn5
         {
           bluemenus();//go to bluemenus
         }
         else if (value==btn6)//or btn6
         {
           redmenus();//go to redmenus
         }
          else if (value==powerbtn)//or if powerbtn
         {
           count=2;//print goodbye
         }
  }
} 
      while (count ==2)//while count variable is equal to 2
     {
        goodbyes();//print goodbye
        break;
     }
  }
}
void start()
{
  count = 1;
  Serial.println("Please choose a menu:");
  Serial.println("Menu 1(Blue LED) press 1");
  Serial.println("Menu 2(Red LED) press 2");
  Serial.println("Menu 3(Both LEDs) press 3");
}
void bluemenus()
{
  Serial.println("");
  Serial.println("");
  Serial.println("Press 4 To control the blue LED");
  Serial.println("Press 5 to go to Menu 2(red control)");
  Serial.println("Press 6 to go to Menu 3(both control)");
  Serial.println("");
  Serial.println("");
  bluemenu=true;
  redmenu=false;
  bothmenu=false;
}
void controlblue()
{
  blueON = !blueON;
  digitalWrite(blueLED,blueON);
}
void redmenus()
{
  Serial.println("");
  Serial.println("");
  Serial.println("Press 4 to Contol the Red LED");
  Serial.println("Press 5 to go to Menu 1(blue control)");
  Serial.println("Press 6 to go to Menu 3(both control)");
  Serial.println("");
  Serial.println("");
  bluemenu=false;
  redmenu=true;
  bothmenu=false;
}
void controlred()
{
  redON = !redON;
  digitalWrite(redLED,redON);
}
void bothmenus()
{
  Serial.println("");
  Serial.println("");
  Serial.println("Press 4 To control both LEDs");
  Serial.println("Press 5 to go to Menu 1(blue control)");
  Serial.println("Press 6 to go to Menu 2(red control)");
  Serial.println("");
  Serial.println("");
  bluemenu=false;
  redmenu=false;
  bothmenu=true;
}
void controlboth()
{
  blueON = !blueON;
  redON = !redON;
  digitalWrite(blueLED, blueON);
  digitalWrite(redLED,redON);
}
void goodbyes()
{
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("GOODBYE");
}