#include "HAL.h"

//Escribe el Nibble menos significativo del byte que recibe.
void lcdWriteNibble(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs);


//Escribe el byte que recibe en el registro indicado.
void lcdWriteByte(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs);


void lcdWriteNibble(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs)
{
	unsigned long sent = 0;
	FT_STATUS valid;
	unsigned char temp;
	temp = (byte << 4) & (0xF0);
	if (rs == SET_IR_ON)
	{
		temp = (temp | (SET_IR_ON)) & (SET_ENABLE_OFF);
		FT_Write(deviceHandler, &temp, sizeof(temp), &sent);
		sleep_for(1ms); //delay de 1 ms
		temp = temp | (SET_ENABLE_ON);
		FT_Write(deviceHandler, &temp, sizeof(temp), &sent);
		sleep_for(3ms);//delay de 3ms.
	}
	else if (rs == SET_DR_ON)
	{
		temp = (temp | (SET_DR_ON)) & (SET_ENABLE_OFF);
		FT_Write(deviceHandler, &temp, sizeof(temp), &sent);
		sleep_for(1ms);//delay de 1 ms
		temp = temp | (SET_ENABLE_ON);
		FT_Write(deviceHandler, &temp, sizeof(temp), &sent);
		sleep_for(3ms);//delay de 3ms.
	}


}

void lcdWriteByte(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs)
{
	lcdWriteNibble(deviceHandler, (byte >> 4), rs); //escribe nybble mas significativo.
	lcdWriteNibble(deviceHandler, byte, rs); //escribe nybble menos significativo.
}

FT_HANDLE * lcdInit(int iDevice)
{
	//Basado en el modelo de los ayudantes
	FT_HANDLE * deviceHandler;

	unsigned char info = 0x00;
	DWORD sizeSent = 0;
	bool found = false;
	FT_STATUS deviceStatus;

	for (int i = 0; (i < 10) && !found; i++)
	{
		deviceStatus = FT_Open(i, deviceHandler);			//Habría que guardar este status

		if (deviceStatus == FT_OK)	//Examples in FTDI guid use 0. But practice shows 1 is usually the case.
		{
		}
		else
			std::cout << "No se puedo abrir el puerto USB " << i << std::endl;
	}
	

	//Configuracion inicial
	lcdWriteNibble(deviceHandler, 0x03, SET_IR_ON);
	sleep_for(4ms); //delay de 4ms.
	lcdWriteNibble(deviceHandler, 0x03, SET_IR_ON);
	sleep_for(100us); //delay de 100 microsegundos.
	lcdWriteNibble(deviceHandler, 0x03, SET_IR_ON);
	lcdWriteNibble(deviceHandler, 0x02, SET_IR_ON);
	//ya esta incializado el modo 4 bits.

	lcdWriteNibble(deviceHandler, 0x02, SET_IR_ON);
	lcdWriteNibble(deviceHandler, 0x08, SET_IR_ON);
	lcdWriteByte(deviceHandler, LCD_DISPLAY_CONTROL, SET_IR_ON);
	lcdWriteByte(deviceHandler, LCD_CLEAR, SET_IR_ON);
	lcdWriteByte(deviceHandler, LCD_ENTRY_MODE_SET, SET_IR_ON);
	return deviceHandler;
}

void lcdWriteIR(FT_HANDLE * deviceHandler, unsigned char valor)
{
	lcdWriteByte(deviceHandler, valor, SET_IR_ON);
}
void lcdWriteDR(FT_HANDLE * deviceHandler, unsigned char valor)
{
	lcdWriteByte(deviceHandler, valor, SET_DR_ON);
}