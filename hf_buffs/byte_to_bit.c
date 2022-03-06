#include "Header.h"
void byte_to_bit(out_buf *b, unsigned char bit, FILE *out, unsigned int *crc)
{
	int tmp;
	if (b->curr_bit > 7)
	{
		b->curr_byte++;
		if (b->curr_byte >= b->sz)
		{
			tmp = crc32(b->sz, crc, b->buf);
			fwrite(b->buf, 1, b->sz, out);
			b->curr_byte = 0;
			counter = 0;
		}
		b->curr_bit = 0;
		b->buf[b->curr_byte] = 0;
	}
	b->buf[b->curr_byte] |= bit << (7 - (b->curr_bit));
	b->curr_bit++;
	counter++;
}