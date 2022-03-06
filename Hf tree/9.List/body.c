#include "Header.h"
void Insert(int a, struct list **head)
{
	struct list *current = (struct list*)malloc(sizeof(struct list)), *newel;
	if (*head == NULL)
	{
		current->next = NULL;
		current->val = a;
		*head = current;
	}
	else
	{
		current->next = head;
		newel = (struct list*)malloc(sizeof(struct list));
		while ((current->next != NULL) && (current->next->val < a))
			current = current->next;
		newel->next = current->next;
		newel->val = a;
		current->next = newel;
	}
}