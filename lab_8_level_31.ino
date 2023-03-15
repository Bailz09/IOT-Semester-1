// Kevin Bailey (200544764@student.georgianc.on.ca)
// Tuesday March 14 2023
// Lab 8 Level 3 LCD choices

//declare variables
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int buttonPin = 6;
String cars[]={"Ferrari", "Ford", "GM", "Maserati", "Cadillac"};
String boats[]={"Skater", "Talon", "Hydrostream", "Martini", "Cigarette"};
String toys[]={"Skidoo", "Seadoo", "SidexSide", "Dirtbike", "Motorcycle"};
String choice[3]={};
int count=-1;

void setup()//setup function runs once
{
Serial.begin(9600);//Serial monitor
lcd.begin (16,2); //Initialize the LCD.
pinMode(buttonPin, INPUT);//setup buttonPin as an INPUT pin 
}	  
void loop()//The loop function runs forever
{ 
  start(); //functions
  car();
  boat(); 
  toy();
  end();
}
void car()
{
  while(count==0)//while count variable is zero print the cars array
  {
    for(int i=0; i<5; i++)//for loop to cycle through the items in the array
    {
      lcd.clear();
	  lcd.setCursor(0,0);
	  lcd.print(cars[i]);
  	  delay(750);
	  if (digitalRead(buttonPin)==HIGH)//checks if the button is pressed
	  {
        lcd.clear(); //clears the lcd screen
        count++;//adds 1 to the count variable
  	    choice[0]=cars[i];//stores the car choice as spot 1 in the choice array
        lcd.setCursor(1, 1);//sets lcd position
        lcd.print(choice[0]);//print users choice
        delay(500);
        break;
      }
    }
  }
}
void boat()
{
  while(count==1)//while count variable is one print the boats array
    {
      for(int i=0; i<5; i++)//for loop to cycle through the items in the array
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(boats[i]);
        delay(750);
        if (digitalRead(buttonPin)==HIGH)//checks to see if the button is pressed
        {
          lcd.clear();//clears the lcd screen
          count++;//adds one to the count variable
  		  choice[1]=boats[i];//stores the boats choice as the second spot in the choice array       
    	  lcd.setCursor(1, 1);//sets lcd position
    	  lcd.print(choice[1]);//prints users choice
    	  delay(500);
          break;
        }
      }
    }
}
void toy()
{
   while(count==2)
     {
       for(int i=0; i<5; i++)//for loop to cycle through the items in the array
       {
         lcd.clear();
		 lcd.setCursor(0,0);
         lcd.print(toys[i]);
         delay(750);
         if (digitalRead(buttonPin)==HIGH)//checks to see if the button is pressed
         {
           lcd.clear();//clears the lcd screen
           count++;//adds one to the count variable
  	 	   choice[2]=toys[i];//stores the toys choice as the third spot in the array
           lcd.setCursor(1, 1);//sets the lcd position
    	   lcd.print(choice[2]);//prints users choice
    	   delay(500);
           break;
         }
       }
     }
}
void end()
{
  while(count==3)
    {
      for(int i=0;i<3;i++)//for loop to cycle through the items in the array
      {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(choice[i]);//prints the choice array
        lcd.setCursor(0,0);
        lcd.print("Your Choices Are");
        delay(500);
         if (digitalRead(buttonPin)==HIGH)//checks if the button is pushed
         {
           count=-1;//sets count variable back to -1, starting the program again
         }
      }
    } 
}
void start()
{
  for (int i=0;i<=4;i++)//for loop to make welcome message scroll
  {
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.print("Press Button");
  	delay(100);
  if (digitalRead(buttonPin)==HIGH)//checks to see if button is pressed
  {
    lcd.clear();
    count=0;//sets count variable to zero, starting the program
    delay(500);
    break;
  }
  }
  for (int i=5;i>=0;i--)//for loop to make second part of welcome message scroll opposite 
  {
    lcd.clear();
    lcd.setCursor(i,1);
    lcd.print("To Start");
  	delay(100);
  if (digitalRead(buttonPin)==HIGH)//check if button is pushed
  {
    lcd.clear();
    count=0;//initializes program
    delay(500);
    break;
  }
  }
}