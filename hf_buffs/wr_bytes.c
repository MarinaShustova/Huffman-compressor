#include "Header.h"
int my_wr_bytes(FILE *out, FILE *info, unsigned int *crc, size_t orsz, codes *cd, out_buf *b, list_tree *h, size_t size)
{
	float res = 0;
	res = 1;
	if (h == NULL) // если нет дерева для разблокирования, мы кодируем, иначе - раскодируем
		compress(out, cd, b, size, info, crc);
	else
		unpress(h, out, orsz, info, crc, size);
	return 0;
}