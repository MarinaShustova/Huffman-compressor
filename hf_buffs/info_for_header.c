#include "Header.h"
int info_for_header(FILE *info, header *h, char *names)
{
	unsigned short l; //name's length
	unsigned long int size; //file's size
	unsigned char *tmmp = NULL;
	fseek(info, 0, SEEK_END);
	size = (unsigned long int)ftell(info);
	fseek(info, 0, SEEK_SET);
	h->full_name = (unsigned char *)names;
	tmmp = full_to_short(names);
	l = (unsigned short)strlen((const char *)tmmp);
	h->flags = 1;
	h->name = tmmp;
	h->nm_l = l;
	h->or_sz = (size_t)size;
	return 0;
}