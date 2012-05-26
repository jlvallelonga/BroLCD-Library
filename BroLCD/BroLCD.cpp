/*
  BroLCD.cpp - Library for Brother LCD code.
  Created by Justin Vallelonga, May 15, 2012.
  Released into the public domain.
*/

#include "Arduino.h"
#include "BroLCD.h"

//TODO: add function to type text

/** default constructor
	ssPin defaults to 10. pauseTime defaults to 400.
*/
BroLCD::BroLCD() {
	pinMode(10, OUTPUT);
	_ssPin = 10;
	_pauseTime = 400;
}

/** constructor overload
	@param ssPin
	slave select pin number. 

	pauseTime defaults to 400.
*/
BroLCD::BroLCD(int ssPin) {
	pinMode(ssPin, OUTPUT);
	_ssPin = ssPin;
	_pauseTime = 400;
}

/** constructor overload
	@param ssPin
	slave select pin number. 
	
	@param pauseTime
	pause time for scrolling animation (in milliseconds)
*/
BroLCD::BroLCD(int ssPin, int pauseTime) {
	pinMode(ssPin, OUTPUT);
	_ssPin = ssPin;
	_pauseTime = pauseTime;
}

/** displays the given int (max 32767) at position 0 on the screen

	@param number
	the number to display
*/
void BroLCD::displayInt(int number) {
	displayIntAtPos(number, 0);
}

/** displays the given string at position 0 on the screen

	@param text[]
	the string to display
*/
void BroLCD::displayText(char text[]) {
	displayStrAtPos(text, 0);
}

/** displays the given int (max 32767) at the beginning of the given line

	@param number
	the number to display

	@param line
	the line to display the number on
*/
void BroLCD::displayInt(int number, int line) {
	if (line == 2)
		displayIntAtPos(number, 16);
	else
		displayIntAtPos(number, 0);
}

/** displays the given string at the beginning of the given line

	@param text[]
	the string to display

	@param line
	the line to display the text on
*/
void BroLCD::displayText(char text[], int line) {
	if (line == 2)
		displayStrAtPos(text, 16);
	else
		displayStrAtPos(text, 0);
}

/** scrolls the given number across the screen on the first line

	@param number
	the number to scroll
*/
void BroLCD::scrollInt(int number) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
	scrollTextAtRange(numAsStr, 0, 15, _pauseTime);
}

/** scrolls the given string across the screen on the first line

	@param text[]
	the string to scroll
*/
void BroLCD::scrollText(char text[]) {
	scrollTextAtRange(text, 0, 15, _pauseTime);
}

/** scrolls the given number across the screen on the given line

	@param number
	the number to scroll

	@param line
	the line to scroll the number on
*/
void BroLCD::scrollInt(int number, int line) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
	scrollText(numAsStr, line);
}

/** scrolls the given string across the screen on the given line

	@param text[]
	the string to scroll

	@param line
	the line to scroll the string on
*/
void BroLCD::scrollText(char text[], int line) {
	if (line == 2)
		scrollTextAtRange(text, 16, 31, _pauseTime);
	else
		scrollTextAtRange(text, 0, 15, _pauseTime);
}

/** scrolls the given number across the screen on the given line with the given pause time

	@param number
	the number to scroll

	@param line
	the line to scroll the number on

	@param pauseTime
	the time delay (in milliseconds) between positions when scrolling
*/
void BroLCD::scrollInt(int number, int line, int pauseTime) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
	scrollText(numAsStr, line, pauseTime);
}

/** scrolls the given string across the screen on the given line with the given pause time

	@param text[]
	the string to scroll

	@param line
	the line to scroll the string on

	@param pauseTime
	the time delay (in milliseconds) between positions when scrolling
*/
void BroLCD::scrollText(char text[], int line, int pauseTime) {
	if (line == 2)
		scrollTextAtRange(text, 16, 31, pauseTime);
	else
		scrollTextAtRange(text, 0, 15, pauseTime);
}

/** scrolls the given number across the screen between the given character positions

	@param number
	the number to scroll

	@param lowerPos
	the lower boundary character position in the scroll range

	@param upperPos
	the upper boundary character position in the scroll range
*/
void BroLCD::scrollIntAtRange(int number, int lowerPos, int upperPos) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
	scrollTextAtRange(numAsStr, lowerPos, upperPos, _pauseTime);
}

/** scrolls the given string across the screen between the given character positions

	@param text[]
	the string to scroll

	@param lowerPos
	the lower boundary character position in the scroll range

	@param upperPos
	the upper boundary character position in the scroll range
*/
void BroLCD::scrollTextAtRange(char text[], int lowerPos, int upperPos) {
	scrollTextAtRange(text, lowerPos, upperPos, _pauseTime);
}

/** scrolls the given number across the screen between the given character positions with the given pause time

	@param number
	the number to scroll

	@param lowerPos
	the lower boundary character position in the scroll range

	@param upperPos
	the upper boundary character position in the scroll range

	@param pauseTime
	the time delay (in milliseconds) between positions when scrolling
*/
void BroLCD::scrollIntAtRange(int number, int lowerPos, int upperPos, int pauseTime) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
	scrollTextAtRange(numAsStr, lowerPos, upperPos, pauseTime);
}

/** scrolls the given string across the screen between the given character positions with the given pause time

	@param text[]
	the string to scroll

	@param lowerPos
	the lower boundary character position in the scroll range

	@param upperPos
	the upper boundary character position in the scroll range

	@param pauseTime
	the time delay (in milliseconds) between positions when scrolling
*/
void BroLCD::scrollTextAtRange(char text[], int lowerPos, int upperPos, int pauseTime) {
	int lenOfText = 0;
	while (text[lenOfText]) {
		lenOfText++;
	}
	for (int startPos = upperPos; startPos >= lowerPos; startPos--) { //for each position on the screen
		//display spaces before the string
		for (int i = lowerPos; i < startPos; i++) {
			displayCharAtPos(' ', i);
		}
		for (int currPos = startPos; currPos <= upperPos; currPos++) {	//from the starting position to the end of the line
			int index = currPos - startPos;
			if (index < lenOfText)									//if the index is within the bounds of the array
				displayCharAtPos(text[index], currPos);				//then display the character in the array at that index
			else
				displayCharAtPos(' ', currPos);						//otherwise you have reached the end of the array and should display spaces
		}
		delay(pauseTime);
	}
	for (int strStartPos = 1; strStartPos < lenOfText; strStartPos++) {
		for (int currPos = lowerPos; currPos <= upperPos; currPos++) {
			int index = (currPos - lowerPos) + strStartPos;
			if (index < lenOfText)									//if the index is within the bounds of the array
				displayCharAtPos(text[index], currPos);				//then display the character in the array at that index
			else
				displayCharAtPos(' ', currPos);
		}
		delay(pauseTime);
	}
	displayCharAtPos(' ', lowerPos);
}

/** displays the given number at the given character position

	@param number
	the number to display

	@param pos
	the character position where to display the number
*/
void BroLCD::displayIntAtPos(int number, int pos) {
	char numAsStr[6];
    String num = String(number);
    num.toCharArray(numAsStr, 6);
    displayStrAtPos(numAsStr, pos);
}

/** displays the given string at the given character position

	@param text[]
	the string to display

	@param pos
	the character position where to display the string
*/
void BroLCD::displayStrAtPos(char text[], int pos) {
	int len = 0;
	digitalWrite(_ssPin, LOW);
	SPI.transfer(192);
	SPI.transfer(pos); //starting position
	while(text[len]) {
		SPI.transfer(text[len]);
		len++;
	}
	digitalWrite(_ssPin, HIGH);
}

/** displays the given character (given as a char) at the given character position

	@param character
	the character to display (given as a char)

	@param pos
	the character position where to display the character
*/
void BroLCD::displayCharAtPos(char character, int pos) {
	digitalWrite(_ssPin, LOW);
	SPI.transfer(192);
	SPI.transfer(pos); //starting position
	SPI.transfer(character);
	digitalWrite(_ssPin, HIGH);
}

/** displays the given character (given as a decimal) at the given character position

	@param character
	the character to display (given as a decimal)

	@param pos
	the character position where to display the number
*/
void BroLCD::displayCharAtPos(int character, int pos) {
	digitalWrite(_ssPin, LOW);
	SPI.transfer(192);
	SPI.transfer(pos); //starting position
	SPI.transfer(character);
	digitalWrite(_ssPin, HIGH);
}

/** sets the global pause time for the scroll animations

	@param pauseTime
	the time delay (in milliseconds) between positions when scrolling
*/
void BroLCD::setPauseTime(int pauseTime) {
	_pauseTime = pauseTime;
}

/** clears the entire screen of everything
*/
void BroLCD::clearScreen() {
	displayStrAtPos("                                ", 0);
}

/** clears the given line of everything

	@param line
	the line to clear
*/
void BroLCD::clearLine(int line) {
	int startPos = 0;
	if (line == 2)
		startPos = 16;
	displayStrAtPos("                ", startPos);
}

/** sets up the LCD for communication. call this before making calls to any other function in this library.
*/
void BroLCD::initialize() {
	SPI.begin();
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	//send 3, 40, 20
	digitalWrite(_ssPin, LOW);
	SPI.transfer(3);
	digitalWrite(_ssPin, HIGH);
	delay(7);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(40);
	digitalWrite(_ssPin, HIGH);
	delay(7);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(20);
	digitalWrite(_ssPin, HIGH);
	delay(40);

	//send 10
	digitalWrite(_ssPin, LOW);
	SPI.transfer(10);
	digitalWrite(_ssPin, HIGH);
	delay(140);

	//send 13, 72, 9
	digitalWrite(_ssPin, LOW);
	SPI.transfer(26);
	digitalWrite(_ssPin, HIGH);
	delay(1);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(72);
	digitalWrite(_ssPin, HIGH);
	delay(1);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(9);
	digitalWrite(_ssPin, HIGH);
	delay(7);
}