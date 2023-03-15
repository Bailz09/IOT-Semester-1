// Kevin Bailey (200544764@student.georgianc.on.ca)
// Wendnesday March 15 2023
// Lab 8 Level 4 LCD yes or no

//declare variables
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int buttonPin2 = 9;//button 2 is connected to pin 9 of the arduino
int buttonPin = 6;//button 1 is connected to pin 6 of the arduino
bool answers[]={};
String questions[]={"Cars", "Boats", "Toys", "Planes", "Music"};
int count=-1;
int yes;
int no;

void setup()//The setup function runs once
{
Serial.begin(9600);//initialize the serial monitor
lcd.begin (16,2); //Initialize the LCD.
pinMode(buttonPin, INPUT);//setup buttonPin as an INPUT pin
pinMode(buttonPin2, INPUT);//setup buttonPin2 as an INPUT pin
}
	  
void loop()//The loop function runs forever
{ 
  start(); //functions
  car();
  boat(); 
  toy();
  plane();
  music();
  end();
}
void car()
{
  while(count==0)//while count variable is zero print the first question
  {
      lcd.clear();
	  lcd.setCursor(0,0);
	  lcd.print("like " + questions[0] + "?");
      lcd.setCursor(0,1);
      lcd.print("yes    no");
  	  delay(750);
	  if (digitalRead(buttonPin)==HIGH)//checks if the button is pushed
	  {
        answers[0]=true;//sets the first spot in the answers array to true or 1
        lcd.clear();
        yes++;//adds 1 to the yes variable
        count++;//adds 1 to the count variable
        lcd.setCursor(0, 1);
        lcd.print("yes");
        delay(500);
        break;
      }
      else if (digitalRead(buttonPin2)==HIGH)
      {
        answers[0]=false;
        lcd.clear();
        no++;//adds 1 to the no variable
        count++;//adds 1 to the count variable
        lcd.setCursor(7, 1);
        lcd.print("no");
        delay(500);
        break;
      } 
  }
}
void boat()
{
  while(count==1)//while count variable is one print the second question
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("like " + questions[1] + "?");
    	lcd.setCursor(0,1);
        lcd.print("yes    no");
        delay(750);
        if (digitalRead(buttonPin)==HIGH)
        {
          answers[1]=true;//sets the 2nd spot in the answers array to true or 1
          lcd.clear();
          yes++;//adds 1 to the yes variable
          count++;//adds 1 to the count variable       
    	  lcd.setCursor(0, 1);
    	  lcd.print("yes");
    	  delay(500);
          break;
        }
    	else if (digitalRead(buttonPin2)==HIGH)
        {
          answers[1]=false;
          lcd.clear();
          no++;//adds 1 to the no variable
          count++;//adds 1 to the count variable  
          lcd.setCursor(7, 1);
          lcd.print("no");
          break;
          delay(500);
        }  
    }
}
void toy()
{
   while(count==2)//while count variable is two print the third question
     {
         answers[2]=true;//sets the 3rd spot in the answers array to true or 1
         lcd.clear();
		 lcd.print("like " + questions[2] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           lcd.clear();
           count++;//adds 1 to the count variable  
           yes++;//adds 1 to the yes variable
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           answers[2]=false;
           lcd.clear();
           no++;//adds 1 to the no variable
           count++;//adds 1 to the count variable  
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void plane()
{
   while(count==3)//while count variable is three print the fourth question
     {
         lcd.clear();
		 lcd.print("like " + questions[3] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           answers[3]=true;//sets the 4th spot in the answers array to true or 1
           lcd.clear();
           count++;
           yes++;//adds 1 to the yes variable
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           answers[3]=false;
           lcd.clear();
           no++;//adds 1 to the no variable
           count++;//adds 1 to the count variable
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void music()
{
   while(count==4)//while count variable is four print the fifth question
     {
         lcd.clear();
		 lcd.print("like " + questions[4] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           answers[4]=true;//sets the 5th spot in the answers array to true or 1
           lcd.clear();
           count++;//adds 1 to the count variable  
           yes++;//adds 1 to the yes variable
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           answers[4]=false;
           lcd.clear();
           no++;//adds 1 to the no variable
           count++;//adds 1 to the count variable  
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void end()
{
  while(count==5)//while count is five print the results
    {
      for(int i=0;i<5;i++)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(yes);
        lcd.setCursor(7,0);
        lcd.print("yes");
        lcd.setCursor(0,1);
        lcd.print(no);
        lcd.setCursor(7,1);
        lcd.print("no");
        delay(500);
        Serial.println(answers[i]); 
         if (digitalRead(buttonPin)==HIGH || digitalRead(buttonPin2) ==HIGH)//checks if either button has been pressed
         {
           count=-1;//set count back to -1, start program again
         }
      }
    }  
}
void start()
{
  	yes=0;
  	no=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Left button=yes");
    lcd.setCursor(0,1);
    lcd.print("Right Button=no");
  	delay(250);
  if (digitalRead(buttonPin)==HIGH || digitalRead(buttonPin2) ==HIGH)//checks if either button is pressed
  {
    lcd.clear();
    count=0;//sets count variable to zero and initializes first question
    delay(500);
  }
}