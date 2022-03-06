#include "Header.h"
void compress(FILE *out, codes *cd, out_buf *b, size_t size, FILE *info, unsigned int *crc)
{
	size_t origsz = size;
	int s, i, tmp, pr;
	counter = 0;
	while (size)
	{
		size_t len = SZ <= size ? SZ : size;
		tmp = my_rd_bytes(info, len, NULL);
		size -= len;
		for (i = 0; (size_t)i < len; i++)
			for (s = 0; s < cd[(int)buff[i]].l;s++)
				byte_to_bit(b, cd[(int)buff[i]].co[s], out, crc);
		pr = (int)(((origsz - size) / (float)origsz) * 100);
		printf("\r%d%%", pr);
	}
	printf("\n");
	tmp = crc32((counter / 8 + 1), crc, b->buf);
	fwrite(b->buf, 1, (counter/8+1), out); //пишется остаток сжатого файла
}