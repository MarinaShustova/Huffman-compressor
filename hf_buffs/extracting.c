#include "Header.h"
int extract_from_archieve(FILE *info, char *files[], int i, int keys, struct stat *in)
{
	list *head = NULL, *head1;
	FILE *out;
	int control = 0, tmp, rd, wr, ord = 0, coinc = 0, j, times = 10, ex, answer, flag;
	unsigned int tsize = 0, size, orsz, crr, *crc = &crr, length, tree_s, file_sz;
	unsigned char *namelen = (unsigned char *)malloc(SIZ), *tempo = NULL, *sizelen = (unsigned char *)malloc(SIZ * 2), *signature = (unsigned char *)malloc(4);
	unsigned char *tree = NULL, *tree_siz = (unsigned char *)malloc(SIZ), *fl = (unsigned char *)malloc(1);
	codes cd[256];
	out_buf b;
	list_tree head_tree;
	struct stat outf;
	head_tree.left = NULL;
	head_tree.right = NULL;
	head_tree.Letter = -1;
	(void)j;
	length = in->st_size;
	tmp = to_list(files, i, &head);
	head1 = head;
	/*while (head)
	{
		printf("%s\n", head->imya);
		head = head->next;
	}
	head = head1;*/
	while (1)
	{
		if ((keys == 0) || (control < i-3))
		{
			tmp = fread(namelen, 1, SIZ, info);
			tmp = ch_to_int(namelen, SIZ);
			tempo = (unsigned char *)malloc(tmp);
			rd = fread(tempo, 1, tmp, info);
			tempo[tmp] = '\0';
			ord++;
			if (keys != 0)
			{
				head = head1;
				coinc = 0;
				times = 0;
					do
					{
						if (!strcmp((const char *)tempo, (const char *)head->imya))
						{
							coinc = 1;
							head = del(&head1, head->imya);
							break;
						}
						head = head->next;
						times++;
					} while (head);
			}
			if ((coinc == 0) && (keys != 0) && (control < i))
			{
				fread(fl, 1, 1, info);
				flag = ch_to_int(fl, 1);
				if (flag == 2)
				{
					memset(sizelen, 0, SIZ);
					tmp = fread(tree_siz, 1, SIZ, info);// длина дерева
					tree_s = ch_to_int(tree_siz, SIZ);
					tree = (unsigned char *)malloc(tree_s);
					tmp = fread(tree, 1, tree_s, info); // дерево
					tmp = fread(sizelen, 1, SIZ * 2, info); // длина закодированного файла
					tsize = ch_to_int(sizelen, SIZ * 2);
					fseek(info, tsize + 8, SEEK_CUR);
				}
				else if (flag == 1)
				{
					fseek(info, 5, SEEK_CUR);
				}
			}
			else if ((coinc == 0) && (keys != 0) && (control == i-1))
			{
				printf("No suitable names\n");
				fclose(info);
			}
			else if ((coinc == 1) && (keys == 0))
			{
				printf("It's impossible!");
				fclose(info);
				return -1;
			}
			else if ((coinc == 1) || (keys == 0))
			{
				ex = stat((const char *)tempo, &outf);
				if (ex != -1)
				{
					printf("There is already %s file in this directory." 
						  "Rewrite it or not?\n1 - rewrite\n0 - file %s.new will be created\n", tempo, tempo);
					scanf("%d", &answer);
					if (answer == 0)
					{
						unsigned char *new_name = (unsigned char *)realloc(tempo, tmp + 3);
					    new_name[tmp] = '.';
						new_name[tmp+1] = 'n';
						new_name[tmp+2] = 'e';
						new_name[tmp+3] = 'w';
						new_name[tmp + 4] = '\0';
						out = fopen((const char *)new_name, "wb");
					}
					else
						out = fopen((const char *)tempo, "wb");
				}
				else 
					out = fopen((const char *)tempo, "wb");
				fread(fl, 1, 1, info);
				flag = ch_to_int(fl, 1);
				if (flag == 2)
				{
					tmp = fread(tree_siz, 1, SIZ, info); // читает длину дерева
					tree_s = ch_to_int(tree_siz, SIZ);
					tree = (unsigned char *)malloc(tree_s);
					tmp = fread(tree, 1, tree_s, info); // читает дерево
					tree[tree_s] = '\0';
					counter = 0;
					create_tree(&head_tree, tree);
					tmp = fread(sizelen, 1, SIZ * 2, info); // читает длину закодированного файла
					size = ch_to_int(sizelen, SIZ * 2);
					tmp = fread(signature, 1, SIZ * 2, info); // читает длину оригинального файла
					orsz = ch_to_int(signature, SIZ * 2);
					*crc = 0xFFFFFFFF;
					wr = my_wr_bytes(out, info, crc, orsz, NULL, NULL, &head_tree, size);
					*crc ^= 0xffffffff;
					fread(signature, 1, SIZ * 2, info);
					tmp = ch_to_int(signature, SIZ * 2);
					if (*crc != (unsigned int)tmp)
					{
						printf("CRC is incorrect problem is with archieve or extracting.\n");
						fclose(info);
						fclose(out);
						control = remove((const char *)tempo);
						return -1;
					}
					head_tree.left = NULL;
					head_tree.right = NULL;
					head_tree.Letter = -1;
				}
				else if (flag == 1)
				{
					int symv;
					symv = fgetc(info); // узнаёт символ
					fread(signature, 1, SIZ * 2, info);
					tmp = ch_to_int(signature, SIZ * 2);//читает количество
					while (tmp) // пишет символ в файл
					{
						fputc(symv, out);
						tmp--;
					}
				}
				fclose(out);
				printf("Success!\n");
				control++;
			}
		}
		if ((control == i) || (ftell(info) == length) || ((head == NULL) && (times == 0)))
			break;
	}
	if (head != NULL)
		while (head)
		{
			printf("There is no %s file in archive.\n", head->imya);
			head = head->next;
		}
	return 0;
}