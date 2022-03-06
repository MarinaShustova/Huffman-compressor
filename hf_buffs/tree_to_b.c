#include "Header.h"
void tree_to_b(list_tree *tmp, FILE *out, unsigned char*arr)
{
	if (!tmp)
		return;
	if (tmp->left && tmp->right)
	{
		arr[counter] = '1';
		counter += 1;
		tree_to_b(tmp->left, out, arr);
		tree_to_b(tmp->right, out, arr);
	}
	else
	{
		arr[counter] = '0';
		arr[counter + 1] = (char)tmp->Letter;
		counter += 2;
		return;
	}
}