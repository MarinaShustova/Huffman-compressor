#include "Header.h"
list *to_tree(list **head)
{
	list *parent = (list*)malloc(sizeof(list)), *current = (list*)malloc(sizeof(list)), *t;
	if (*head == NULL)
		return *head;
	current = *head;
	while (current->next != NULL)
	{
		parent->Letter = -1;
		parent->fr = current->fr + current->next->fr;
		parent->left = current;
		parent->right = current->next;
		if (current->next->next == NULL)
		{
			*head = parent;
			break;
		}
		if (parent->fr < current->next->next->fr)
		{
			parent->prev = NULL;
			parent->next = current->next->next;
			*head = parent;
		}
		else
		{
			*head = current->next->next;
			t = *head;
			while ((t->next != NULL) && (parent->fr > t->next->fr))
				t = t->next;
			parent->prev = t;
			parent->next = t->next;
			t->next = parent;
			t->next->prev = parent;
		}
		parent->left->next = NULL;
	//	parent->right->prev->next = NULL;
		parent->right->prev = NULL;
		parent->right->next->prev = NULL;
		parent->right->next = NULL;
		/*parent->left->prev->next = NULL;
		parent->left->prev = NULL;
		parent->left->next->prev = NULL;*/
		current = *head;
		parent = (list*)malloc(sizeof(list));
	}
	return *head;
}