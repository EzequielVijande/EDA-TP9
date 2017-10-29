#include "HitachiLCD.h"

HitachiLCD::HitachiLCD(int iDevice) //falta verificar la inicializacion correcta.
{
	Init = false;
	FT_HANDLE * device_handler;
	lcdInit(iDevice);
	cadd = 1;
}
HitachiLCD:: ~HitachiLCD()
{
	//Hacer close del handler.
}
bool HitachiLCD::lcdInitOk()const
{
	return Init;
}
FT_STATUS HitachiLCD::lcdGetError()
{

}
bool HitachiLCD::lcdClear()
{
	lcdWriteIR(device_handler, LCD_CLEAR);
	cadd = 1;
	return true;
}
bool HitachiLCD::lcdClearToEOL()
{

}
basicLCD& HitachiLCD::operator<<(const unsigned char c)
{

}
basicLCD& HitachiLCD::operator<<(const unsigned char * c)
{

}
bool HitachiLCD::lcdMoveCursorUp()
{

}
bool HitachiLCD::lcdMoveCursorDown()
{

}
bool HitachiLCD::lcdMoveCursorRight()
{

}
bool HitachiLCD::lcdMoveCursorLeft()
{

}
bool HitachiLCD::lcdSetCursorPosition(const cursorPosition pos)
{

}
cursorPosition HitachiLCD::lcdGetCursorPosition()
{

}

