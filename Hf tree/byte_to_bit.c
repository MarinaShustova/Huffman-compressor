#include "Header.h"
void byte_to_bit(out_buf *b, unsigned char bit, FILE *out)
{
	if (b->curr_bit > 7)
	{
		if (b->curr_byte > b->sz)
			b->curr_byte = 0;
		else
			b->curr_byte++;
		b->curr_bit = 0;
	/*	if (b->curr_byte > b->sz)
		{
			fwrite(b->buf, 1, b->sz, out);
		}*/
		b->buf[b->curr_byte] = 0;
	}
	b->buf[b->curr_byte] |= bit << (7 - (b->curr_bit));
	b->curr_bit++;
}