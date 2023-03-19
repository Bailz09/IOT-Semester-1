// C++ code
//
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
char input;
bool power=true;
bool blueON=false;
bool redON=false;
bool bluemenu=false;
bool redmenu=false;
bool bothmenu=false;
bool goodbye=false;
int count=0;
void setup() 
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(redLED, OUTPUT);
  Serial.println("Welcome please hit power button to continue");
}

void loop() 
{
  
 // while(Serial.available()==0)
 // {
 // }
 
  if (IrReceiver.decode()) 
  {
    
    IrReceiver.resume();
    value = IrReceiver.decodedIRData.command;
    //Serial.println(value);
     if (value==powerbtn)
     {
       count = 1;
       Serial.println("Please choose a menu:");
  	   Serial.println("Menu 1(Blue LED) press 1");
  	   Serial.println("Menu 2(Red LED) press 2");
  	   Serial.println("Menu 3(Both LEDs) press 3");
     }
	if (value==btn1)
    {
      Serial.println("");
      Serial.println("");
      Serial.println("Press 4 To control the blue LED");
      Serial.println("Press 5 to go to Menu 2(red control)");
      Serial.println("Press 6 to go to Menu 3(both control)");
      bluemenu=true;
      redmenu=false;
      bothmenu=false;    
    }
       else if (value==btn2)
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
       else if (value==btn3)
       {
         Serial.println("");
         Serial.println("");
         Serial.println("Press 4 to Contol both LEDs");
         Serial.println("Press 5 to go to Menu 1(blue control)");
         Serial.println("Press 6 to go to Menu 2(red control)");
         Serial.println("");
         Serial.println("");
         bluemenu=false;
         redmenu=false;
         bothmenu=true;
       }

     
     while (bluemenu && count==1)
     {
       if (IrReceiver.decode()) 
       {
         IrReceiver.resume();
         value = IrReceiver.decodedIRData.command;
       	if(value==btn4)
       	{
          blueON = !blueON;
          digitalWrite(blueLED,blueON);
        }
         else if (value==btn5)
         {
           Serial.println("Press 4 to Contol the Red LED");
           Serial.println("Press 5 to go to Menu 1(blue control)");
           Serial.println("Press 6 to go to Menu 3(both control)");
           Serial.println("");
           Serial.println("");
           bluemenu=false;
           redmenu=true;
           bothmenu=false;
         }
         else if (value==btn6)
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
         else if (value==powerbtn)
         {
           count=2;
         }
       }
   }
   while (redmenu && count ==1)
     {
       if (IrReceiver.decode()) 
       {
         IrReceiver.resume();
         value = IrReceiver.decodedIRData.command;
       	if(value==btn4)
       	{
          redON = !redON;
          digitalWrite(redLED,redON);
        }
         else if (value==btn5)
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
         else if (value==btn6)
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
          else if (value==powerbtn)
         {
           count=2;
         }
  }
}
   while (bothmenu && count ==1)
     {
       if (IrReceiver.decode()) 
       {
         IrReceiver.resume();
         value = IrReceiver.decodedIRData.command;
       	if(value==btn4)
       	{
          blueON = !blueON;
          redON = !redON;
          digitalWrite(blueLED, blueON);
          digitalWrite(redLED,redON);
        }
         else if (value==btn5)
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
         else if (value==btn6)
         {
           Serial.println("");
           Serial.println("");
           Serial.println("Press 4 To control the red LED");
           Serial.println("Press 5 to go to Menu 1(blue control)");
           Serial.println("Press 6 to go to Menu 3(both control)");
           Serial.println("");
           Serial.println("");
           bluemenu=false;
           redmenu=true;
           bothmenu=false;
         }
          else if (value==powerbtn)
         {
           count=2;
         }
  }
} 
      while (count ==2)
     {
           Serial.println("");
     	   Serial.println("");
           Serial.println("");
           Serial.println("GOODBYE");
         break;
     }
  }
}
