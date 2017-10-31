#pragma once
//Modulo que contiene la estructura del  display Hitachi HD44780. 

//FALTA LA VALIDACION DE TODAS LAS FUNCIONES!

#include "BasicLCD.h"
#include "HAL.h"

#define FTD2XX_EXPORTS
#include "ftd2xx.h"

class HitachiLCD : public basicLCD
{
public:
	HitachiLCD(int iDevice);
	virtual ~HitachiLCD();
	virtual bool lcdInitOk()const;
	virtual bool lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const unsigned char c);
	virtual basicLCD& operator<<(const unsigned char * c);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();

private:
	bool Init;
	FT_HANDLE * device_handler;
	virtual void lcdUpdateCursor();
	unsigned char Hcadd();
};