#include "Header.h"
void printlist(struct list *head, char *out)
{
	FILE *outname;
	if ((out[0] == 's')||(out[0] != '-'))
		while (head)
		{
			printf("%d\n", head->val);
			head = head->next;
		}
	else if ((out[0] == '-') && (out[1] == 'o'))
	{
		outname = fopen(out + 2, "w");
		while (head)
		{
			fprintf(outname, "%d\n", head->val);
			head = head->next;
		}
		fclose(outname);
	}
}