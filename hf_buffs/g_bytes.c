#include"Header.h"
int get_bytes(size_t sz, unsigned char *buffer, char size)
{
	memset(buffer, 0, size);
	while (sz > 0 && size > 0)
	{
		size--;
		*(buffer + size) = sz & 0xFF;
		sz >>= 8;
	}
	if (sz != 0)
		return 5;
	return 0;
}