#include "HAL.h"

//Defincion de los pins del display.

#define PIN_P0 0
#define PIN_P1 1
#define PIN_P2 2
#define PIN_P3 3
#define PIN_P4 4
#define PIN_P5 5
#define PIN_P6 6
#define PIN_P7 7

//Representacion de cada bit.

#define LCD_E (1<< (PIN_P0)) //Bit de Enable
#define LCD_RS (1 << (PIN_P1)) //Bit de Register Select

#define LCD_D4 (1<< (PIN_P4))  //Bits D4-D7
#define LCD_D5 (1 << (PIN_P5))
#define LCD_D6 (1<< (PIN_P6))
#define LCD_D7 (1 << (PIN_P7))


//Instrucciones del LCD
#define LCD_CLEAR 0x01
#define LCD_RETURN_HOME 0x02

//Mascaras.
#define SET_IR_ON (~(LCD_RS))
#define SET_DR_ON (LCD_RS)
#define SET_ENABLE_ON (LCD_E)
#define SET_ENABLE_OFF (~(LCD_E))

//Escribe el Nibble menos significativo del byte que recibe.
void lcdWriteNibble(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs);


//Escribe el byte que recibe en el registro indicado.
void lcdWriteByte(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs);


void lcdWriteNibble(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs)
{
	unsigned short sent = 0;
	FT_STATUS valid;
	unsigned char temp;
	temp = (byte << 4) & (0xF0);
	if (rs == SET_IR_ON)
	{
		temp = (temp | (SET_IR_ON)) & (SET_ENABLE_OFF);
		FT_write(deviceHandler, &temp, sizeof(temp), &sent);
		//delay de 1 ms
		temp = temp | (SET_ENABLE_ON);
		FT_write(deviceHandler, &temp, sizeof(temp), &sent);
		//delay de 3ms.
	}
	else if (rs == SET_DR_ON)
	{
		temp = (temp | (SET_DR_ON)) & (SET_ENABLE_OFF);
		FT_write(deviceHandler, &temp, sizeof(temp), &sent);
		//delay de 1 ms
		temp = temp | (SET_ENABLE_ON);
		FT_write(deviceHandler, &temp, sizeof(temp), &sent);
		//delay de 3ms.
	}


}

void lcdWriteByte(FT_HANDLE * deviceHandler, unsigned char byte, unsigned char rs)
{
	lcdWriteNibble(deviceHandler, (byte >> 4), rs);
	lcdWriteNibble(deviceHandler, byte, rs);
}