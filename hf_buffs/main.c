#include "Header.h"
int main(int argc, char*argv[])
{
	FILE *info, *out = NULL;
	int tmp = 0, i, keys, an = 0;
	unsigned int rcr, *crc = &rcr;
	struct stat in;
	unsigned char *signature = (unsigned char *)malloc(4);
	*crc = 0xFFFFFFFF;
	i = argc - 3;
	if (argv[1][0] == 'H')
	{
		printf("This is an archievator which uses Huffman's algorithm.\n"
				"Function should be called this way: -a|e|l|d archieve_name.huf file_1_name.* ...\n"
				"Here\n"
				"-a is an adding key which means that files from the list will be added to archive\n"
				"-e is an extracting key which means that files from the list will be extracted from archive\n"
				"-l is a listing key which means that names, sizes and compression ratios will be printed on the screen\n"
				"-d is a deliteing key which means that files from the list will be delited from the archive.\n");
		return 0;
	}
	if (argc < 3)
	{
		printf("Not enough parametres please watch help. To call help type Help.\n");
		return -1;
	}
	else if (argc != 3)
		an = 1;
	else if (argc == 3)
		an = 0;
		if (argv[1][1] == 'a')
		{
			if (an == 0)
			{
				printf("Nothing to add.\n");
				return -1;
			}
			keys = stat((const char *)argv[2], &in);
			out = fopen(argv[2], "ab");
			if (out == NULL)
			{
				printf("Writing error, file is closed for writing.\n");
				return -1;
			}
			if (keys == -1)
				fputs("SIGN", out);
			tmp = add_into_arc(out, argv, i);
			fclose(out);
		}
		else if (argv[1][1] == 'e')
		{
			//stat на чтение
			if (stat(argv[2], &in) == -1)
			{
				printf("No archive found\n");
				return -1;
			}
			info = fopen(argv[2], "rb");
			tmp = fread(signature, 1, 4, info);
			if (!strcmp((const char *)signature, "SIGN"))
			{
				printf("Unknown signature.\n");
				fclose(info);
				return -1;
			}
			tmp = extract_from_archieve(info, argv, argc, an, &in);
			fclose(info);
		}
		else if (argv[1][1] == 'l')
		{
			if (argc != 3)
			{
				printf("Incorrect call\n");
				return 0;
			}
			if (stat(argv[2], &in) == -1)
			{
				printf("No archive found\n");
				return -1;
			}
			info = fopen(argv[2], "rb");
			tmp = fread(signature, 1, 4, info);
			if (!strcmp((const char *)signature, "SIGN"))
			{
				printf("Unknown signature.\n");
				fclose(info);
				return -1;
			}
			//проверка на чтение stat
			tmp = listing(info, &in);
		}
		else if (argv[1][1] == 'd')
		{
			//	unsigned char *new_name;
			if (stat(argv[2], &in) == -1)
			{
				printf("No archive found\n");
				return -1;
			}
			info = fopen(argv[2], "ab");
			if (info == NULL)
			{
				printf("Archive is closed for writing.\n");
				return -1;
			}
			fclose(info);
			info = fopen(argv[2], "rb");
			tmp = fread(signature, 1, 4, info);
			if (!strcmp((const char *)signature, "SIGN"))
			{
				printf("Unknown signature.\n");
				fclose(info);
				return -1;
			}
			if (an == 0)
			{
				tmp = remove(argv[2]);
				return 0;
			}
			tmp = deliting(info, argv, i, &in);
			fclose(info);
			tmp = remove(argv[2]);
			tmp = rename("tmp.huf", (const char *)argv[2]);
		}
		else
			printf("I don't know what to do now.\n");
  return 0;
}