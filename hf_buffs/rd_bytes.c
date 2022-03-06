#include "Header.h"
int my_rd_bytes(FILE *input, size_t len, unsigned int *crc)
{
	int tmp;
	size_t n;
	n = fread(buff, 1, len, input);
	if ((n != len) && (!feof(input)))
		return 3;
	tmp = crc32(len, crc, NULL);
	if (tmp != 0)
		return 4;
	return 0;
}