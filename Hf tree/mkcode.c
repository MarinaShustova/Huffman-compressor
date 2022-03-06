#include "Header.h"
void mkcode(list *h, int i, char *c, codes *code)
{
	if (!h)
		return;
	if (h->left)
	{
		c[i] = 0;
		mkcode(h->left, i + 1, c, code);
	}
	if (h->right)
	{
		c[i] = 1;
		mkcode(h->right, i + 1, c, code);
	}
	if (h->Letter > -1)
	{
		code[h->Letter].l = i;
		memcpy(code[h->Letter].co, c, i);
	}
}