#include "Header.h"
unsigned int ch_to_int(unsigned char *buffer, char size)
{
	unsigned int res = 0, i;
	for (i = 0; i < size; i++)
	{
		res = (res << 8) | buffer[i];
	}
	return res;
}