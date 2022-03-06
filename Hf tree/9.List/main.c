#include "Header.h"
int main(int argc, char *argv[])
{
	FILE *info;
	int  *a = NULL;
	int i, num, total_l = 0, curr_l = 0, res = 0, j;
	struct list *head;
	head = (struct list*)malloc(sizeof(struct list));
	head = NULL;
	if ((argc == 2) && (!strcmp(argv[1], "?")))
	{
		printf("This programm can create a sorted list in ascending order with given array of numbers.\n"
			"  %s a1 ... aN|-iFILE1 [s]|-oFILE2\n"
			"Where\n  a1 ... aN is an array you should type by yourself\n"
			"  -i is an input file key\n"
			"  FILE1 is a name of file you want to give to program\n"
			"  s is a screen key which means that result will be printed on the screen\n"
			"  -o is an output file key which means that result will be printed in file\n"
			"  FILE2 is a name of file in which result will be printed\n", argv[0]);
		return 0;
	}
	if ((argc>2) && (argv[argc-1][0] == '-') && (argv[argc-1][1] == 'o'))
		printf("Result is printed in file %s with adress C:\\Users\\1\\Documents\\Visual Studio 2015\\Projects\\9.List\n", argv[2] + 2);
	if (!argv[1])
	{
		printf("Call example\n"
			"  %s a1 ... aN|-iFILE1 [s]|-oFILE2\n"
			"Where\n  a1 ... aN is an array you should type by yourself\n"
			"  -i is an input file key\n"
			"  FILE1 is a name of file you want to give to program\n"
			"  s is a screen key which means that result will be printed on the screen\n"
			"  -o is an output file key which means that result will be printed in file\n"
			"  FILE2 is a name of file in which result will be printed\n", argv[0]);
		return -1;
	}
	if ((argv[1][0] == '-') && (argv[1][1] == 'i'))
	{
		info = fopen(argv[1] + 2, "r");
		if (info == NULL)
		{
			printf("Reading error, no file");
			return -1;
		}
		while (1)
		{
			fscanf(info, "%d", &num);
			if (feof(info))
			{
				fclose(info);
				break;
			}
			if (curr_l >= total_l)
			{
				total_l += G;
				a = (int *)realloc(a, total_l * sizeof(int));
			}
			Insert(num, &head);
			curr_l++;
		}
		if (head == NULL)
		{
			printf("File %s is empty\n", argv[1]+2);
			return -1;
		}
		printlist(head, argv[2]);
		free(a);
		Freelist(head);
		return 0;
	}
	else
	{
		a = malloc(sizeof(int) * (argc));
		for (i = 0; i < argc - 1; i++)
		{
			
			for (i = 1; i < argc; i++)
			{
				if (argv[i][0] != '-')
				for(j = 0; argv[i][j] != '\0'; j++)
					res = res * 10 + argv[i][j] - '0';
				Insert(res, &head);
				res = 0;
			}
		}
		printlist(head, argv[argc-1]);
		free(a);
		Freelist(head);
		return 0;
	}
}