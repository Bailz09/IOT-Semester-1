// C++ code
//

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

//making a string array
int buttonPin2 = 9;
int buttonPin = 6;
String questions[]={"Cars", "Boats", "Toys", "Planes", "Music"};
int count=-1;
int yes;
int no;

void setup()
{
Serial.begin(9600);
lcd.begin (16,2); //Initialize the LCD.
pinMode(buttonPin, INPUT);
pinMode(buttonPin2, INPUT);
}
	  
void loop()
{ 
  start(); 
  car();
  boat(); 
  toy();
  plane();
  music();
  end();
}
void car()
{
  while(count==0)
  {
      lcd.clear();
	  lcd.setCursor(0,0);
	  lcd.print("like " + questions[0] + "?");
      lcd.setCursor(0,1);
      lcd.print("yes    no");
  	  delay(750);
	  if (digitalRead(buttonPin)==HIGH)
	  {
        
        lcd.clear();
        yes++;
        count++;
        lcd.setCursor(0, 1);
        lcd.print("yes");
        delay(500);
        break;
      }
      else if (digitalRead(buttonPin2)==HIGH)
      {
        lcd.clear();
        no++;
        count++;
        lcd.setCursor(7, 1);
        lcd.print("no");
        delay(500);
        break;
      }          
  }
}
void boat()
{
  while(count==1)
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("like " + questions[1] + "?");
    	lcd.setCursor(0,1);
        lcd.print("yes    no");
        delay(750);
        if (digitalRead(buttonPin)==HIGH)
        {
          lcd.clear();
          yes++;
          count++;       
    	  lcd.setCursor(0, 1);
    	  lcd.print("yes");
    	  delay(500);
          break;
        }
    	else if (digitalRead(buttonPin2)==HIGH)
        {
          lcd.clear();
          no++;
          count++;
          lcd.setCursor(7, 1);
          lcd.print("no");
          delay(500);
          break;
        }     
    }
}
void toy()
{
   while(count==2)
     {
         lcd.clear();
		 lcd.print("like " + questions[2] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           lcd.clear();
           count++;
           yes++;
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           lcd.clear();
           no++;
           count++;
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void plane()
{
   while(count==3)
     {
         lcd.clear();
		 lcd.print("like " + questions[3] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           lcd.clear();
           count++;
           yes++;
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           lcd.clear();
           no++;
           count++;
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void music()
{
   while(count==4)
     {
         lcd.clear();
		 lcd.print("like " + questions[4] + "?");
    	 lcd.setCursor(0,1);
         lcd.print("yes    no");
         delay(750);
         if (digitalRead(buttonPin)==HIGH)
         {
           lcd.clear();
           count++;
           yes++;
           lcd.setCursor(0, 1);
    	   lcd.print("yes");
    	   delay(500);
           break;
         }
     	 else if (digitalRead(buttonPin2)==HIGH)
         {
           lcd.clear();
           no++;
           count++;
           lcd.setCursor(7, 1);
           lcd.print("no");
           delay(500);
           break;
         }
      }
}
void end()
{
  while(count==5)
    {
      for(int i=0;i<3;i++)
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
         if (digitalRead(buttonPin)==HIGH || digitalRead(buttonPin2) ==HIGH)
         {
           count=-1;
         }
      }
    }  
}
void start()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Left button=yes");
    lcd.setCursor(0,1);
    lcd.print("Right Button=no");
  	delay(250);
  if (digitalRead(buttonPin)==HIGH || digitalRead(buttonPin2) ==HIGH)
  {
    lcd.clear();
    count=0;
    delay(500);
  }
}