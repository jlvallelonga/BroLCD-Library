/*
  BroLCD.h - Library for Brother LCD code.
  Created by Justin Vallelonga, May 15, 2012.
  Released into the public domain.
*/
#ifndef BroLCD_h
#define BroLCD_h

#include "Arduino.h"
#include "../SPI/SPI.h"

class BroLCD
{
  public:
    BroLCD(int ssPin);
    BroLCD(int ssPin, int waitTime);
    void displayText(char text[]);
    void displayText(char text[], int line);
	void scrollText(char text[]);
	void scrollText(char text[], int line);
	void scrollText(char text[], int line, int waitTime);
	void scrollTextAtRange(char text[], int lowerPos, int upperPos);
	void scrollTextAtRange(char text[], int lowerPos, int upperPos, int waitTime);
	void displayStrAtPos(char text[], int pos);
	void displayCharAtPos(char character, int pos);
	void setWaitTime(int waitTime);
	void clearScreen();
	void clearLine(int line);
	void begin();
  private:
	int _ssPin;
	int _waitTime;
};

#endif