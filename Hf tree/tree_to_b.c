#include "Header.h"
void tree_to_b(list *tmp, FILE *out, unsigned char*arr)
{
	if (!tmp)
		return;
	if (tmp->left && tmp->right)
	{
//		fprintf(out, "1");
//		*arr++ = '1';
//		*arr++;
		arr[counter] = '1';
		counter += 1;
		tree_to_b(tmp->left, out, arr);
		tree_to_b(tmp->right, out, arr);
	} 
	else
	{
//		*arr++ = '0';
//		*arr++ = (char)tmp->Letter;
		arr[counter] = '0';
		arr[counter + 1] = (char)tmp->Letter;
		counter += 2;
		return;
	}
}