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
    BroLCD();
    BroLCD(int ssPin);
    BroLCD(int ssPin, int pauseTime);
    void displayInt(int number);
    void displayText(char text[]);
    void displayInt(int number, int line);
    void displayText(char text[], int line);
	void scrollInt(int number);
	void scrollText(char text[]);
	void scrollInt(int number, int line);
	void scrollText(char text[], int line);
	void scrollInt(int number, int line, int pauseTime);
	void scrollText(char text[], int line, int pauseTime);
	void scrollIntAtRange(int number, int lowerPos, int upperPos);
	void scrollTextAtRange(char text[], int lowerPos, int upperPos);
	void scrollIntAtRange(int number, int lowerPos, int upperPos, int pauseTime);
	void scrollTextAtRange(char text[], int lowerPos, int upperPos, int pauseTime);
	void displayIntAtPos(int number, int pos);
	void displayStrAtPos(char text[], int pos);
	void displayCharAtPos(char character, int pos);
	void displayCharAtPos(int character, int pos);
	void setPauseTime(int pauseTime);
	void clearScreen();
	void clearLine(int line);
	void initialize();
  private:
	int _ssPin;
	int _pauseTime;
};

#endif