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
	FT_Close(*device_handler);
	//Hacer close del handler.
}
bool HitachiLCD::lcdInitOk()const
{
	return Init;
}
FT_STATUS HitachiLCD::lcdGetError()
{
	DWORD * lpdwAmountInRxQueue;
	DWORD * lpdwAmountInTxQueue;
	DWORD * lpdwEventStatus;
	FT_STATUS ret = FT_GetStatus(*device_handler, lpdwAmountInRxQueue, lpdwAmountInTxQueue, lpdwEventStatus);
	return ret;
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

