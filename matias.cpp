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
#define IS_VALID_POS(pos) (IS_VALID_ROW((pos).row))

bool lcdClearToEOL()
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
	FT_STATUS state;
	while ((cadd <= limit) && (!error))
	{
		state = lcdWriteDR(device_handler, ' '); //imprimo espacios, simulando que borro el display, letra por letra.
		if (state != FT_OK)
		{
			error = true;
		}
		else
		{
			cadd++;
		}
	}
	cadd = cadd_aux; //regreso el cursor a la posición que tenia antes de ejecutar la función.
	if (!error)
	{
		lcdUpdateCursor();
	}

	return error;  //devuelve true si hubo error, false si no hubo error
	
}

bool lcdSetCursorPosition(const cursorPosition pos)
{
	if
}
virtual cursorPosition lcdGetCursorPosition() = 0;

/*int main(void)
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
	lcd << "demo de char *";
	sleep(3);
	string str = "demo de str";
	lcd << str;

	return 0;
}*/