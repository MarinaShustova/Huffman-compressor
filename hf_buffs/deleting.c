#include "Header.h"
int deliting(FILE *info, char *files[], int i, struct stat *in)
{
	FILE *out;
	int coinc, j, tmp, rd, wr, answer, flag;
	unsigned char *namelen = (unsigned char *)malloc(SIZ), *tempo = NULL;
	unsigned char *signature = (unsigned char *)malloc(4), *tree = NULL;
	unsigned char *fl = (unsigned char *)malloc(1), *b5 = (unsigned char *)malloc(5);
	size_t size, orsz, tree_sz;
	out = fopen("tmp.huf", "wb");
	fputs("SIGN", out);
	while (1)
	{
		tmp = fread(namelen, 1, SIZ, info);
		tmp = ch_to_int(namelen, SIZ);
		tempo = (unsigned char *)malloc(tmp);
		rd = fread(tempo, 1, tmp, info);
		tempo[tmp] = '\0';
		coinc = 0;
		for (j = 3; j < i+3; j++)
		{
			if (strcmp((const char*)tempo, (const char *)files[j]) == 0)
			{
				coinc = 1;
				break;
			}
		}
		if (coinc == 0)
		{
			
			fread(fl, 1, 1, info);
			flag = ch_to_int(fl, 1);
			fwrite(namelen, 1, SIZ, out); //����� ����� �����
			fputs((const char *)tempo, out); //����� ���
			if (flag == 2)
			{
				fread(namelen, 1, SIZ, info); // ������ ����� ������
				fwrite(namelen, 1, SIZ, out); //����� ����� ������
				tree_sz = ch_to_int(namelen, SIZ);
				tree = (unsigned char *)malloc(tree_sz);
				fread(tree, 1, tree_sz, info); //������ ������
				fwrite(tree, 1, tree_sz, out); //����� ������
				fread(signature, 1, SIZ * 2, info); //������ ������ ������� �����
				size = ch_to_int(signature, SIZ * 2);
				fwrite(signature, 1, SIZ * 2, out); //����� ������ ������� �����
				fread(signature, 1, SIZ * 2, info); //������ ������ ������������� �����
				fwrite(signature, 1, SIZ * 2, out); //����� ������ ������������� �����
				while (size)
				{
					size_t l = SZ <= size ? SZ : size;
					fread(buff, 1, l, info);
					fwrite(buff, 1, l, out);
					size -= l;
				}
				fread(signature, 1, SIZ * 2, info); //������ crc
				fwrite(signature, 1, SIZ * 2, out); //����� crc
			}
			else if (flag == 1)
			{
				fread(b5, 1, 5, info); //����� ��, ��� ��� �����
				fwrite(b5, 1, 5, out);
			}
		}
		else
		{
			fread(fl, 1, 1, info);
			flag = ch_to_int(fl, 1);
			if (flag == 2)
			{
				fread(namelen, 1, SIZ, info); // ������ ����� ������
				tree_sz = ch_to_int(namelen, SIZ);
				fseek(info, tree_sz, SEEK_CUR);
				fread(signature, 1, SIZ * 2, info); //������ ������ ������� �����
				size = ch_to_int(signature, SIZ * 2);
				fseek(info, size + 8, SEEK_CUR);
			}
			else if (flag == 1)
			{
				fseek(info, 5, SEEK_CUR);
			}
		}
		if (ftell(info) == in->st_size)
			break;
	}
	if (ftell(out) == 4)
	{
		printf("Archive became empty. Delete it?\n1 - Yes\n0 - No\n");
		scanf("%d", &answer);
		if (answer == 1)
		{
			fclose(out);
			remove("tmp.huf");
		}
		else
			fclose(out);
	}
	else
		fclose(out);
	return 0;
}