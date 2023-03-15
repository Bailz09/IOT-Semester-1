// C++ code
//

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

//making a string array

int buttonPin = 6;
String cars[]={"Ferrari", "Ford", "GM", "Maserati", "Cadillac"};
String boats[]={"Skater", "Talon", "Hydrostream", "Martini", "Cigarette"};
String toys[]={"Skidoo", "Seadoo", "SidexSide", "Dirtbike", "Motorcycle"};
String choice[3]={};
int count=0;
void setup()
{
Serial.begin(9600);
lcd.begin (16,2); //Initialize the LCD.
pinMode(buttonPin, INPUT);
}

void loop()
{ 
  car();
  boat(); 
  toy();
  end();
}
void car()
{
  while(count==0)
  {
    for(int i=0; i<5; i++)
    {
      lcd.clear();
	  lcd.setCursor(0,0);
	  lcd.print(cars[i]);
  	  delay(750);
    
	  if (digitalRead(buttonPin)==HIGH)
	  {
        lcd.clear();
        count++;
  	    choice[0]=cars[i];
        lcd.setCursor(1, 1);
        lcd.print(choice[0]);
        delay(750);
        break;
      }
    }
  }
}
void boat()
{
  while(count==1)
    {
      for(int i=0; i<5; i++)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(boats[i]);
        delay(750);
        
        if (digitalRead(buttonPin)==HIGH)
        {
          lcd.clear();
          count++;
  		  choice[1]=boats[i];       
    	  lcd.setCursor(1, 1);
    	  lcd.print(choice[1]);
    	  delay(750);
          break;
        }
      }
    }
}
void toy()
{
   while(count==2)
     {
       for(int i=0; i<5; i++)
       {
         lcd.clear();
		 lcd.setCursor(0,0);
         lcd.print(toys[i]);
         delay(750);
         
         if (digitalRead(buttonPin)==HIGH)
         {
           lcd.clear();
           count++;
  	 	   choice[2]=toys[i];
           lcd.setCursor(1, 1);
    	   lcd.print(choice[2]);
    	   delay(750);
           break;
         }
       }
     }
}
void end()
{
  while(count==3)
    {
      for(int i=0;i<3;i++)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(choice[i]);
        delay(500);
      }
    }
}