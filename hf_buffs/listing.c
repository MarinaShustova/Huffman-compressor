#include "Header.h"
int listing(FILE *info, struct stat *in)
{
	int tmp, rd, flag;
	unsigned int size, orsz;
	unsigned char *namelen = (unsigned char *)malloc(SIZ), *tempo = NULL, *sizelen = NULL;
	unsigned char *tree_sz = (unsigned char *)malloc(SIZ);
	unsigned char *fl = (unsigned char *)malloc(1);
	printf("Archive has this files:\n");
	while (1)
	{
		if (ftell(info) != in->st_size)
		{
			tmp = fread(namelen, 1, SIZ, info); //читает длину имени
			tmp = ch_to_int(namelen, SIZ); //читает имя
			tempo = (unsigned char *)malloc(tmp);
			rd = fread(tempo, 1, tmp, info);
			tempo[tmp] = '\0';
			printf("\t%s\n", tempo);//пишет имя
			fread(fl, 1, 1, info);
			flag = ch_to_int(fl, 1);
			if (flag == 2)
			{
				rd = fread(tree_sz, 1, SIZ, info);
				size = ch_to_int(tree_sz, SIZ);
				fseek(info, size, SEEK_CUR);
				sizelen = (unsigned char *)malloc(SIZ * 2);
				tmp = fread(sizelen, 1, SIZ * 2, info);
				size = ch_to_int(sizelen, SIZ * 2);
				printf("\t\t%u bytes compressed size\n", size);
				tmp = fread(sizelen, 1, SIZ * 2, info);
				orsz = ch_to_int(sizelen, SIZ * 2);
				printf("\t\t%u bytes original size\n", orsz);
				tmp = 100 - (int)((size / (float)orsz) * 100);
				printf("\t\tcompression ratio is %d%%\n", tmp);
				fseek(info, size + 4, SEEK_CUR);
			}
			else if (flag == 1)
			{
				sizelen = (unsigned char *)malloc(SIZ * 2);
				printf("5 bytes compressed size, ");
				fseek(info, 1, SEEK_CUR);
				fread(sizelen, 1, SIZ * 2, info);
				orsz = ch_to_int(sizelen, SIZ * 2);
				printf("%u bytes original size, ", orsz);
				tmp = 100 - (int)((5 / (float)orsz) * 100);
				printf("compression ratio is %d%%\n", tmp);
			}
			else if (flag == 0)
			{
				printf("file is empty\n");
			}
		}
		else
			break;
	}
	fclose(info);
	return 0;
}