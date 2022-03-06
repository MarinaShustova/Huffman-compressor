#include "Header.h"
void crCode(list_tree *h, codes *code)
{
	char c[256];
	memset((void *)code, 0, sizeof(codes) * 256);
	mkcode(h, 0, c, code);
}