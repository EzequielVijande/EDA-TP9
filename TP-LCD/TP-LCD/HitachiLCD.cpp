#include "HitachiLCD.h"

#define ERROR_HCADD 0xFF
#define HITACHI_OFFSET_SECOND_LINE 0x40

#define BEGIN_OF_FIRST_LINE 1
#define END_OF_FIRST_LINE 16
#define BEGIN_OF_SECOND_LINE 17
#define END_OF_SECOND_LINE 32
#define IS_ON_FIST_LINE(x) (((x >= BEGIN_OF_FIRST_LINE) && (x <= END_OF_FIRST_LINE)))
#define IS_ON_SECOND_LINE(x) (((x >= BEGIN_OF_SECOND_LINE) && (x <= END_OF_SECOND_LINE)))
#define MIN_ROW 0
#define MAX_ROW 1
#define MIN_COL 0
#define MAX_COL 15
#define IS_VALID_ROW(x) (((x >= MIN_ROW) && (x <= MAX_ROW)))
#define IS_VALID_COL(x) (((x >= MIN_COL) && (x <= MAX_COL)))
#define IS_VALID_POS(pos) ((IS_VALID_ROW(pos.row) && IS_VALID_COL(pos.column)))

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
bool HitachiLCD::lcdInitOk()
{
	return Init;
}
bool HitachiLCD::lcdGetError()
{
	bool ret = false;
	DWORD * lpdwAmountInRxQueue = nullptr;
	DWORD * lpdwAmountInTxQueue = nullptr;
	DWORD * lpdwEventStatus = nullptr;
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
	FT_STATUS state = FT_OK; //esto hay que igualarlo a la funcion de lcdwrite, pero para eso la funcion debe devolver algun status.
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
	int limit = 0;
	if (IS_ON_FIST_LINE(cadd))
	{
		limit = END_OF_FIRST_LINE;
	}
	else if (IS_ON_SECOND_LINE(cadd))
	{
		limit = END_OF_SECOND_LINE;
	}
	else
	{
		error = true;
	}
	if (!error)
	{
		while (cadd <= limit)
		{
			lcdWriteDR(device_handler, ' '); //imprimo espacios, simulando que borro el display, letra por letra.
			cadd++;
		}
		cadd = cadd_aux; //regreso el cursor a la posición que tenia antes de ejecutar la función.
		lcdUpdateCursor();
	}
	
	return error;  //devuelve true si hubo error, false si no hubo error

}
basicLCD& HitachiLCD::operator<<(const unsigned char c)
{
	lcdWriteDR((this->device_handler), c);
	return *this;
};

basicLCD& HitachiLCD::operator<<(const unsigned char * c)
{
	unsigned int i = 0;
	while (c[i] != '\0')
	{
		lcdWriteDR((this->device_handler), c[i]);
		i++;
	}

	return *this;
};

bool HitachiLCD::lcdMoveCursorUp()
{
	if ((cadd >= 1) && (cadd <= 8)) //primer línea del hitachiLCD
	{
		return false; //no se puede mover hacia arriba
	}
	else if ((cadd > 8) && (cadd <= 16))  //segunda línea del hitachiLCD
	{
		cursorPosition newPos;
		newPos.column = 1;
		newPos.row = cadd - 8;
		lcdSetCursorPosition(newPos);
		return true;
	}
	else   //el cadd esta fuera del hitachiLCD
	{
		return false;
	}
}

bool HitachiLCD::lcdMoveCursorDown()
{
	if ((cadd >= 1) && (cadd <= 8)) //primer línea del hitachiLCD
	{
		cursorPosition newPos;
		newPos.column = cadd;
		newPos.row = 2;
		lcdSetCursorPosition(newPos);
		return true;
	}
	else if ((cadd > 8) && (cadd <= 16))  //segunda línea del hitachiLCD
	{
		return false; //no se puede mover hacia abajo
	}
	else   //el cadd esta fuera del hitachiLCD
	{
		return false;
	}
}

bool HitachiLCD::lcdMoveCursorRight()
{
	if ((cadd >= 1) && (cadd < 16)) //no llegue al final
	{
		cursorPosition newPos;
		if (cadd > 8)
		{
			newPos.row = 2;
			newPos.column = cadd - 8 + 1;
		}
		else if (cadd < 8)
		{
			newPos.row = 1;
			newPos.column = cadd + 1;
		}
		else if (cadd == 8)
		{
			newPos.row = 2;
			newPos.column = 1;
		}
		lcdSetCursorPosition(newPos);
		return true;
	}
	else //ya no lo puedo mover
	{
		return false;
	}
}

bool HitachiLCD::lcdMoveCursorLeft()
{
	if ((cadd > 1) && (cadd <= 16)) //no llegue al principio
	{
		cursorPosition newPos;
		if (cadd > 9)
		{
			newPos.row = 2;
			newPos.column = cadd - 8 - 1;
		}
		else if (cadd <9)
		{
			newPos.row = 1;
			newPos.column = cadd - 1;
		}
		else if (cadd == 9)
		{
			newPos.row = 1;
			newPos.column = 8;
		}
		lcdSetCursorPosition(newPos);
		return true;
	}
	else //ya no lo puedo mover
	{
		return false;
	}
}

bool HitachiLCD::lcdSetCursorPosition(const cursorPosition pos)
{
	switch (pos.row)
	{
	case 1:
		cadd = pos.column;
		break;
	case 2:
		cadd = pos.column + 8;
		break;
	}
	lcdUpdateCursor();
}

cursorPosition HitachiLCD::lcdGetCursorPosition()
{
	cursorPosition currPos;
	if ((cadd >= 1) && (cadd <= 8))
	{
		currPos.row = 1;
		currPos.column = cadd;
	}
	else if ((cadd > 8) && (cadd <= 16))
	{
		currPos.column = cadd + 8;
		currPos.row = 2;
	}
	else
	{
		currPos.column = -1;
		currPos.row = -1;
	}
	return currPos;
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
	else if ((cadd >= 17) && (cadd <= 32))  //segunda línea del hitachiLCD
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
