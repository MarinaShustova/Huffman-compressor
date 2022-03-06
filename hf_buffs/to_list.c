#include "Header.h"
int to_list(char *files[], int val, list **head)
{
	list *current = (struct list*)malloc(sizeof(struct list)), *newel;
	int j=3;
	*head = NULL;
	while (val-3)
	{
		if (*head == NULL)
		{
			current->next = NULL;
			current->imya = (unsigned char *)files[j];
			*head = current;
		}
		else
		{
			newel = (list*)malloc(sizeof(list));
			newel->imya = (unsigned char *)files[j];
			newel->next = *head;
			*head = newel;
		}
		val--;
		j++;
	}
	return 0;
}