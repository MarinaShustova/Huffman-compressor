#include "Header.h"
void unpress(list_tree *h, FILE *out, size_t orsz, FILE *info, unsigned int *crc, size_t size)
{
	int i = 0, curr_bit = 8, tmp, ft = 1, pr;
	list_tree *reserved_head;
	reserved_head = h;
	while (orsz)
	{	
		size_t l = SZ < size ? SZ : size;
		if (curr_bit > 7)
		{
			i++;
			curr_bit = 0;
			if ((i == l) || (ft == 1))
			{
				ft = 0;
				if (size != 0)
				{
					tmp = my_rd_bytes(info, l, crc);
					size -= l;
					pr = (int)(((orsz - size) / (float)orsz) * 100);
					printf("\r%d%%", pr);
				}
				i = 0;
			}
		}
		if ((buff[i] & (1<<7)) != 0)
		{
			h = h->right;
			buff[i] <<= 1;
			curr_bit++;
		}
		else if ((buff[i] & (1<<7)) == 0)
		{
			h = h->left; 
			buff[i] <<= 1;
			curr_bit++;
		}
		if (h->Letter != -1)
		{
			fputc((char)h->Letter, out);
			h = reserved_head;
			orsz--;
		}
	}
	printf("\n");
}