#include "Header.h"
unsigned char *full_to_short(char *full)
{
	//char *tmp = full;
	unsigned int l;
	int j = 0, c = 0, t = 0;
	(void)j;
	l = strlen((const char*)full);
	t = l;
	full += l - 1;
	while ((*full != '\\') && (l != 0))
	{
		c++;
		l--;
		full--;
	}
	return (unsigned char*)(full + 1);
}