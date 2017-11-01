#include "HitachiLCD.h"


basicLCD& HitachiLCD::operator<<(const unsigned char c)
{
	lcdWriteDR((this->device_handler), c);
	return *this;
};

basicLCD& HitachiLCD::operator<<(const unsigned char * c)
{
	unsigned int i = 0;
	while (c[i]!='\0')
	{
		lcdWriteDR((this->device_handler), c[i]);
		i++;
	}

	return *this;
};