#include "Header.h"
int add_into_arc(FILE *out, char *files[], int i)
{
	FILE *info;
	header h;
	struct stat in;
	size_t size, pos1, pos2;
	int j = 3, tmp, rd, wr, exist;
	unsigned int crr, *crc = &crr;
	unsigned char *namelen = (unsigned char *)malloc(SIZ),  *signature = (unsigned char *)malloc(4);
	codes cd[256];
	out_buf b;
	memset(cd, 0, (sizeof(codes)*256));
	b.buf = NULL;
	while (i)
	{
		exist = stat(files[j], &in);
		if (exist == -1)
		{
			printf("File %s does not exist.\n", files[j]);
			i--;
			j++;
		}
		else
		{
			if (!strcmp((const char *)files[2], (const char *)files[j]))
			{
				printf("You are trying to add current archieve. This version of arcivator can't do that.\n");
				i--;
				j++;
			}
			else
			{
				info = fopen(files[j], "rb");
				//проверка на чтение stat
				if (in.st_size == 0)
				{
					unsigned char *fl = (unsigned char *)malloc(1);
					tmp = info_for_header(info, &h, files[j]);
					tmp = get_bytes(h.nm_l, namelen, SIZ);
					fwrite((const char *)namelen, 1, SIZ, out); //пишет длину имени
					fputs((const char *)h.name, out); //пишет имя
					tmp = get_bytes(0, fl, 1);
					fwrite(fl, 1, 1, out); //пишет флаг пустого файла
					fclose(info);
				}
				else
				{
					tmp = info_for_header(info, &h, files[j]);
					size = h.or_sz;
					tmp = get_bytes(h.nm_l, namelen, SIZ);
					fwrite((const char *)namelen, 1, SIZ, out); //пишет длину имени
					fputs((const char *)h.name, out); //пишет имя
					*crc = 0xFFFFFFFF;
					pos1 = ftell(out);
					tmp = d_main(out, info, cd, &b); // пишутся флаг, длина дерева, дерево, размер сжатого файла в байтах
					pos2 = ftell(out);
					if ((pos2 - pos1) > 6)
					{
						tmp = get_bytes(size, signature, 2 * SIZ);
						fwrite((const char *)signature, 1, SIZ * 2, out); // размер оригинального файла
						wr = my_wr_bytes(out, info, crc, h.or_sz, cd, &b, NULL, size); // пишется сам файл
						*crc ^= 0xffffffff;
						tmp = get_bytes(*crc, signature, SIZ * 2); //не сигнатура, а массив под 4 байта
						fwrite(signature, 1, SIZ * 2, out);
					}
					fclose(info);
				}
				info = NULL;
				printf("File %s\n", files[j]);
				printf("Success!\n");
				i--;
				j++;
			}
		}
	}
	return 0;
}