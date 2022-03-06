#include "Header.h"
void PrintInFile(list *tr, FILE *out, unsigned char *arr, out_buf *c)
{
//	int i;
	counter = 0;
	tree_to_b(tr, out, arr);
	arr[counter] = '\0';
	fwrite(arr, 1, strlen(arr), out);
	/*for (i = 0; i < c->sz; i++)
	{
		byte_to_bit(c, arr[i], out);
	}*/
	return;
}