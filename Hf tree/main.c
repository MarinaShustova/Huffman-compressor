#include "Header.h"
int main(int argc, char *argv[])
{
	FILE *info, *out;
	int mas[256] = {0};
	int s, i, j = 0;
	list *head = NULL;
	codes cd[256];
	size_t size;
	out_buf b;
	unsigned char *arr = NULL;
	info = fopen(argv[1], "rb");
	fseek(info, 0, SEEK_END);
	size = ftell(info);
	fseek(info, 0, SEEK_SET);
	while (!feof(info))
	{
		s = fgetc(info);
		if (s > 0)
			mas[s]++;
	}
	fseek(info, 0, SEEK_SET);
	for (i = 0; i < 256; i++)
	{
		if (mas[i] != 0)
		{
			head = to_list(&head, mas[i], i);
			j++;
		}
	}
	head = to_tree(&head);
	arr = (unsigned char *)malloc(3*j - 1);
	out = fopen("Codes2.txt", "wb");
	PrintInFile(head, out, arr, &b);
	crCode(head, cd);
	b.sz = 0;
	for (i = 0; i < 256; i++)
	{
		if(cd[i].l != 0)
			b.sz += cd[i].l * mas[i];
	}
	b.sz = (b.sz % 8 == 0) ? (b.sz / 8) : (b.sz / 8 + 1);
	b.curr_bit = 8;
	b.curr_byte = b.sz +1;
	b.buf = (unsigned char *)malloc(b.sz);
	compress(out, cd, info, &b);
	fclose(info);
	fclose(out);
	return 0;
}