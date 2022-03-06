#include "Header.h"
list *del(list **head, unsigned char *imya)
{
	list *tmp, *tmp1;
	tmp = *head;
	tmp1 = tmp;
	if (!strcmp((const char *)tmp->imya, (const char *)imya))
	{
		tmp1 = tmp->next;
		free(tmp);
		return tmp1;
	}
	while (strcmp((const char *)tmp->next->imya, (const char *)imya))
		tmp = tmp->next;
	tmp1 = tmp->next;
	tmp->next = tmp1->next;
	free(tmp1);
	return *head;
}