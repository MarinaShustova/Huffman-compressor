#include "Header.h"
void PrintInFile(list_tree *tr, FILE *out, unsigned char *arr, out_buf *c)
{
	//	int i;
	c->sz = 0;
	counter = 0;
	tree_to_b(tr, out, arr);
	arr[counter] = '\0';
	fwrite((const char *)arr, 1, counter, out);
	return;
}