#include "Header.h"
list *to_list(list **head, int code, int pos)
{
	struct list *current = (list*)malloc(sizeof(list)), *newel;
	if (*head == NULL)
	{
		current->next = NULL;
		current->prev = NULL;
		current->left = NULL;
		current->right = NULL;
		current->fr = code;
		current->Letter = pos;
		*head = current;
	}
	else
	{
		current->next = *head;
		current->prev = NULL;
		newel = (struct list*)malloc(sizeof(struct list));
		newel->left = NULL;
		newel->right = NULL;
		while ((current->next != NULL) && (current->next->fr <= code))
			current = current->next;
		if ((current->prev == NULL) && (current->next != NULL) && (current->next->fr > code) && (current != *head))
		{
				newel->next = current->next;
				newel->prev = current->prev;
				newel->fr = code;
				newel->Letter = pos;
				current->next->prev = newel;
				*head = newel;
		}
		else if ((current->prev == NULL) && (current->fr >= code))
		{
			newel->next = current;
			newel->prev = current->prev;
			newel->fr = code;
			newel->Letter = pos;
			current->prev = newel;
			*head = newel;
		}
		else if ((current->next == NULL) && (current->fr <= code))
		{
			newel->next = NULL;
			newel->prev = current;
			newel->fr = code;
			newel->Letter = pos;
			current->next = newel;
		}
		else 
		{
			newel->next = current->next;
			newel->prev = current;
			newel->fr = code;
			newel->Letter = pos;
			current->next = newel;
		}
	}
	return *head;
}