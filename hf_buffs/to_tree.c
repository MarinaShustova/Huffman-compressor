#include "Header.h"
list_tree *to_tree(list_tree **head)
{
	list_tree *parent = (list_tree*)malloc(sizeof(list_tree)), *current = (list_tree*)malloc(sizeof(list_tree)), *t;
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
		parent->right->prev = NULL;
		parent->right->next->prev = NULL;
		parent->right->next = NULL;
		current = *head;
		parent = (list_tree*)malloc(sizeof(list_tree));
	}
	return *head;
}