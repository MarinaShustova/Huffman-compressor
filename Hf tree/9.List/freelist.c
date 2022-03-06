#include "Header.h"
void Freelist(struct list *head)
{
	struct list *h;
	while (head)
	{
		h = head->next;
		free(head);
		head = h;
	}
}