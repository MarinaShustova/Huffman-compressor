#include "Header.h"
void create_tree(list_tree *h, unsigned char *tib)
{
	list_tree *newel_r = NULL, *newel_l = NULL;
	if (!h)
		return;
	if (tib[counter] == '1')
	{
		if (h->left == NULL)
		{
			newel_l = (list_tree *)malloc(sizeof(list_tree));
			newel_l->left = NULL;
			newel_l->right = NULL;
			h->left = newel_l;
			h->Letter = -1;
			counter++;
			create_tree(h->left, tib);
		}
		newel_r = (list_tree *)malloc(sizeof(list_tree));
		newel_r->left = NULL;
		newel_r->right = NULL;
		h->right = newel_r;
		create_tree(h->right, tib);
		return;
	}
//	(tib[counter] == '1') &&
	/*if ((h->right == NULL) && (h->left != NULL))
	{
		newel = (list_tree *)malloc(sizeof(list_tree));
		newel->left = NULL;
		newel->right = NULL;
		h->right = newel;
		h->Letter = -1;
		counter++;
		create_tree(h->right, tib);
	}*/
	if (tib[counter] == '0')
	{
		h->Letter = (int)tib[counter + 1];
		counter++;
		counter++;
		return;
	}
}