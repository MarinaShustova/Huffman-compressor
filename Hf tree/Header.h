#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct out_buf {
	unsigned char *buf;
	size_t sz;
	size_t curr_byte;
	unsigned char curr_bit;
}out_buf;
typedef struct c {
	int l;
	char co[256];
} codes;
typedef struct list {
	int fr;
	int Letter;
	struct  list *next;
	struct	list *prev;
	struct  list *right;
	struct	list *left;
} list;
list *to_list(list **h, int code, int pos);
list *to_tree(list **head);
void PrintInFile(list *tr, FILE *out, unsigned char *arr, out_buf *c);
void tree_to_b(list *head, FILE *out, unsigned char *arr);
void mkcode(list *h, int i, char *c, codes *code);
void crCode(list *h, codes *code);
void compress(FILE *out, codes *cd, FILE *info, out_buf *b);
void byte_to_bit(out_buf *b, unsigned char bit, FILE *out);
int counter;