#include <BroLCD.h>
#include <SPI.h>
BroLCD lcd(10);

void setup() {
  lcd.begin();
  
}

void loop() {
  lcd.clearScreen();
  lcd.displayText("line 1", 1);
  delay(1000);
  lcd.clearLine(1);
  lcd.displayText("line 2", 2);
  delay(1000);
  lcd.clearLine(2);
  
  lcd.displayText("clear line 1", 1);
  delay(1000);
  lcd.clearLine(1);
  delay(500);
  lcd.displayText("clear line 2", 2);
  delay(1000);
  lcd.clearLine(2);
  delay(500);
  lcd.displayText("clear screen", 1);
  lcd.displayText("clear screen", 2);
  delay(1000);
  lcd.clearScreen();
  delay(500);
  
  lcd.setWaitTime(200);
  lcd.scrollText("scroll line 1");
  lcd.scrollText("scroll line 2", 2);
  lcd.displayText("really fast");
  lcd.setWaitTime(100);
  lcd.scrollText("REALLY FAST", 2);
  lcd.displayText("really slow");
  lcd.setWaitTime(500);
  lcd.scrollText("SLOW", 2);
  
  lcd.displayText("in subsections");
  lcd.setWaitTime(200);
  lcd.scrollTextAtRange("hello", 16, 23);
  lcd.scrollTextAtRange("hello", 16, 23);
  lcd.scrollTextAtRange("hello", 23, 31);
  lcd.scrollTextAtRange("hello", 23, 31);
  lcd.clearLine(1);
  
  lcd.displayText("in subsections", 2);
  lcd.scrollTextAtRange("hello", 7, 15);
  lcd.scrollTextAtRange("hello", 7, 15);
  lcd.scrollTextAtRange("hello", 0, 7);
  lcd.scrollTextAtRange("hello", 0, 7);
  lcd.clearLine(2);
  
}
