#include<iostream>
using namespace std;

#include "HAL.h"
#include "HitachiLCD.h"

int main(void)
{
	FT_HANDLE * handle = lcdInit(2);

	lcdWriteIR(handle, (LCD_DISPLAY_CONTROL | (0x04)));
	lcdWriteDR(handle, 'A');
	cout << "" << endl;
	getchar();



	/*
	HitachiLCD lcd(2);
	char c = 0;
	do
	{
		scanf(&c);
		switch (c)
		{
		case 'd':
			lcdMoveCursorRight();
			break;
		case 'w':
			lcdMoveCursorUp();
			break;
		case 'a':
			lcdMoveCursorLeft();
			break;
		case 'b':
			lcdMoveCursorRight();
			break;
		case 'c':
			lcdClear();
			break;
		case 'x':
			lcdClearToEOL();
			break;
		case 'g':
			lcdGetCursorPosition();
			break;
		default:
			lcd << c;
		}
	} while (c != 'q');
	lcd << "demo de c_string";
	sleep(3);
	string str = "demo de str_c++";
	lcd << str;
	*/
	return 0;
}