#include "Header.h"
int d_main(FILE *out, FILE *info, codes *cd, out_buf *b)
{
	int mas[256] = { 0 };
	int s, i = 0, j = 0, tmp, remain;
	list_tree *head = NULL;
	size_t b_siz;
	unsigned char *arr = NULL, *numers = NULL, *tree = NULL, *amount = (unsigned char *)malloc(4), *fl = (unsigned char *)malloc(1);
	while (!feof(info))
	{
		s = fgetc(info);
		if (s >= 0)
			mas[s]++;
	}
	fseek(info, 0, SEEK_SET);
	for (i = 0; i < 256; i++)
	{
		if (mas[i] != 0)
		{
			head = to_list_for_tree(&head, mas[i], i);
			j++;
		}
	}
	if (j == 1)
	{
		tmp = get_bytes(1, fl, 1);
		fwrite(fl, 1, 1, out); //пишет флаг файла из одного символа
		fputc(head->Letter, out); //пишет символ
		tmp = get_bytes(head->fr, amount, SIZ * 2);
		fwrite(amount, 1, SIZ * 2, out); //пишет количество
	}
	else
	{
		tmp = get_bytes(2, fl, 1);
		fwrite(fl, 1, 1, out); //пишет флаг стандартного файла
		head = to_tree(&head);
		arr = (unsigned char *)malloc(3 * j - 1);
		numers = (unsigned char *)malloc(SIZ * 2);
		tree = (unsigned char *)malloc(SIZ);
		tmp = get_bytes((3 * j - 1), tree, SIZ);
		fwrite(tree, 1, SIZ, out); // пишет длину дерева
		PrintInFile(head, out, arr, b); // пишет дерево в файл
		crCode(head, cd);
		b->sz = 0;
		for (i = 0; i < 256; i++)
		{
			if (cd[i].l != 0)
				b->sz += cd[i].l * mas[i];
		}
		remain = 8 - (b->sz % 8);
		b->sz = (b->sz % 8 == 0) ? (b->sz / 8) : (b->sz / 8 + 1);
		b->curr_bit = 8;
		b->buf = (unsigned char *)malloc(SZ);
		tmp = get_bytes(b->sz, numers, SIZ * 2);
		b->sz = SZ;
		b->curr_byte = -1;
		fwrite(numers, 1, SIZ * 2, out); // размер сжатого файла
	}
	return 0;
}