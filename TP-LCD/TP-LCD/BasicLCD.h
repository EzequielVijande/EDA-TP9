#pragma once

#include <iostream>
#include <string>

//Modulo que contiene la estructura de una clase abstracta que compone un LCD
//cualquiera.

struct cursorPosition
{
	int row;
	int column;
};
class basicLCD
{
public:

	basicLCD();
	virtual ~basicLCD();
	virtual bool lcdInitOk() = 0;
	virtual bool lcdGetError() = 0;
	virtual bool lcdClear() = 0;
	virtual bool lcdClearToEOL() = 0;
	virtual basicLCD& operator<<(const char c) = 0;
	virtual basicLCD& operator<<(const char * c) = 0;
	virtual basicLCD& operator<<(std::string str) = 0;
	virtual bool lcdMoveCursorUp() = 0;
	virtual bool lcdMoveCursorDown() = 0;
	virtual bool lcdMoveCursorRight() = 0;
	virtual bool lcdMoveCursorLeft() = 0;
	virtual bool lcdSetCursorPosition(const cursorPosition pos) = 0;
	virtual cursorPosition lcdGetCursorPosition() = 0;
protected:
	int cadd;
	bool error;
	virtual void lcdUpdateCursor() = 0;
};