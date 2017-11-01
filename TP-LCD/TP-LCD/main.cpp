#include<iostream>
using namespace std;

#define FTD2XX_EXPORTS
#include "ftd2xx.h"


int main(void)
{
	HitachiLCD lcd;
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

	return 0;
}