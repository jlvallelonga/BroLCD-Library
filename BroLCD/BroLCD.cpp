/*
  BroLCD.cpp - Library for Brother LCD code.
  Created by Justin Vallelonga, May 15, 2012.
  Released into the public domain.
*/

#include "Arduino.h"
#include "BroLCD.h"

//TODO: add function to type text

BroLCD::BroLCD(int ssPin) {
	pinMode(ssPin, OUTPUT);
	_ssPin = ssPin;
	_waitTime = 400;
}

BroLCD::BroLCD(int ssPin, int waitTime) {
	pinMode(ssPin, OUTPUT);
	_ssPin = ssPin;
	_waitTime = waitTime;
}

void BroLCD::displayText(char text[]) {
	displayStrAtPos(text, 0);
}

void BroLCD::displayText(char text[], int line) {
	if (line == 2)
		displayStrAtPos(text, 16);
	else
		displayStrAtPos(text, 0);
}

void BroLCD::scrollText(char text[]) {
	scrollTextAtRange(text, 0, 15, _waitTime);
}

void BroLCD::scrollText(char text[], int line) {
	if (line == 2)
		scrollTextAtRange(text, 16, 31, _waitTime);
	else
		scrollTextAtRange(text, 0, 15, _waitTime);
}

void BroLCD::scrollText(char text[], int line, int waitTime) {
	if (line == 2)
		scrollTextAtRange(text, 16, 31, waitTime);
	else
		scrollTextAtRange(text, 0, 15, waitTime);
}

void BroLCD::scrollTextAtRange(char text[], int lowerPos, int upperPos) {
	scrollTextAtRange(text, lowerPos, upperPos, _waitTime);
}

void BroLCD::scrollTextAtRange(char text[], int lowerPos, int upperPos, int waitTime) {
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
		delay(waitTime);
	}
	for (int strStartPos = 1; strStartPos < lenOfText; strStartPos++) {
		for (int currPos = lowerPos; currPos <= upperPos; currPos++) {
			int index = (currPos - lowerPos) + strStartPos;
			if (index < lenOfText)									//if the index is within the bounds of the array
				displayCharAtPos(text[index], currPos);				//then display the character in the array at that index
			else
				displayCharAtPos(' ', currPos);
		}
		delay(waitTime);
	}
	displayCharAtPos(' ', lowerPos);
}

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

void BroLCD::displayCharAtPos(char character, int pos) {
	digitalWrite(_ssPin, LOW);
	SPI.transfer(192);
	SPI.transfer(pos); //starting position
	SPI.transfer(character);
	digitalWrite(_ssPin, HIGH);
}

void BroLCD::setWaitTime(int waitTime) {
	_waitTime = waitTime;
}

void BroLCD::clearScreen() {
	displayStrAtPos("                                ", 0);
}

void BroLCD::clearLine(int line) {
	int startPos = 0;
	if (line == 2)
		startPos = 16;
	displayStrAtPos("                ", startPos);
}

void BroLCD::begin() {
	SPI.begin();
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV128);

	//send 3, 40, 20
	digitalWrite(_ssPin, LOW);
	SPI.transfer(3);          //3
	digitalWrite(_ssPin, HIGH);
	delay(7);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(40);          //40
	digitalWrite(_ssPin, HIGH);
	delay(7);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(20);          //20
	digitalWrite(_ssPin, HIGH);
	delay(40);

	//send 10
	digitalWrite(_ssPin, LOW);
	SPI.transfer(10);          //10
	digitalWrite(_ssPin, HIGH);
	delay(140);

	//send 13, 72, 9
	digitalWrite(_ssPin, LOW);
	//  SPI.transfer(0x0D);          //13
	SPI.transfer(26);          //26
	digitalWrite(_ssPin, HIGH);
	delay(1);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(72);          //72
	digitalWrite(_ssPin, HIGH);
	delay(1);
	digitalWrite(_ssPin, LOW);
	SPI.transfer(9);          //9
	digitalWrite(_ssPin, HIGH);
	delay(7);
}