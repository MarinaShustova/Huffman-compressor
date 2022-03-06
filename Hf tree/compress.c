#include "Header.h"
void compress(FILE *out, codes *cd, FILE *info, out_buf *b)
{
	int s, i;
	counter = 0;
	while (!feof(info))
	{
		s = fgetc(info);
		if (s != -1)
			for (i = 0; i < cd[s].l; i++)
				byte_to_bit(b, cd[s].co[i], out);
	}
	fwrite(b->buf, 1, b->sz, out);
}