#include "HitachiLCD.h"

#define ERROR_HCADD 0xFF
#define HITACHI_OFFSET_SECOND_LINE 0x40

HitachiLCD::HitachiLCD(int iDevice) //falta verificar la inicializacion correcta.
{
	Init = false;
	
	device_handler = lcdInit(iDevice);
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
bool HitachiLCD::lcdGetError()
{
	bool ret = false;
	DWORD * lpdwAmountInRxQueue;
	DWORD * lpdwAmountInTxQueue;
	DWORD * lpdwEventStatus;
	FT_STATUS state = FT_GetStatus(*device_handler, lpdwAmountInRxQueue, lpdwAmountInTxQueue, lpdwEventStatus);
	if (state == FT_OK)
	{
		ret = true;
	}
	else
	{
		error = true;
	}
	return ret;
}
bool HitachiLCD::lcdClear()
{
	bool ret = false;
	FT_STATUS state; //esto hay que igualarlo a la funcion de lcdwrite, pero para eso la funcion debe devolver algun status.
	lcdWriteIR(device_handler, LCD_CLEAR);
	if (state == FT_OK)
	{
		cadd = 1;
		ret = true;
	}
	else
	{
		error = true;
	}
	return ret;
}
bool HitachiLCD::lcdClearToEOL()
{
	int cadd_aux = cadd;
	lcdWriteIR(device_handler, LCD_CLEAR);
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

void HitachiLCD::lcdUpdateCursor()
{
	lcdWriteIR(device_handler, LCD_SET_DDRAM_ADRESS | Hcadd());
}

unsigned char HitachiLCD::Hcadd()
{
	unsigned char hCadd = 0;
	if ((cadd >= 1) && (cadd <= 16)) //primer línea del hitachiLCD
	{
		hCadd = (unsigned char)cadd - 1;
	}
	else if ((cadd >= 1) && (cadd <= 16))  //segunda línea del hitachiLCD
	{
		hCadd = (unsigned char)cadd - 1;
		hCadd += HITACHI_OFFSET_SECOND_LINE;
	}
	else   //el cadd esta fuera del hitachiLCD
	{
		hCadd = ERROR_HCADD;
	}
	return hCadd;
}

