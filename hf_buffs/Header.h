#ifndef PROG_H
#define PROG_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys\\stat.h>
#include <malloc.h>
#define SZ 65536
#define SIZ 2
typedef struct list
{
	unsigned char *imya;
	struct list *next;
} list;
typedef struct header {
	unsigned char flags;
	unsigned char *full_name;
	unsigned short nm_l;
	unsigned char *name;
	size_t or_sz;
	size_t sz;
} header;
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
typedef struct list_tree {
	unsigned int fr;
	int Letter;
	struct  list_tree *next;
	struct	list_tree *prev;
	struct  list_tree *right;
	struct	list_tree *left;
} list_tree;
unsigned char *full_to_short(char *full);
int get_bytes(size_t sz, unsigned char *buff, char size);
int ch_to_int(unsigned char *buff, char size);
int my_wr_bytes(FILE *out, FILE *info, unsigned int *crc, size_t orsz, codes *cd, out_buf *b, list_tree *h, size_t size);
int my_rd_bytes(FILE *input, size_t len, unsigned int *crc);
int crc32(size_t size, unsigned int *crc, unsigned char *bb);
int info_for_header(FILE *info, header *h, char *names);
int add_into_arc(FILE *out, char *files[], int i);
int extract_from_archieve(FILE *info, char *files[], int i, int keys, struct stat *in);
int listing(FILE *info, struct stat *in);
int deliting(FILE *info, char *files[], int i, struct stat *in);
int to_list(char *files[], int val, list **head);
list *del(list **head, unsigned char *imya);
list_tree *to_list_for_tree(list_tree **h, int code, int pos);
list_tree *to_tree(list_tree **head);
void PrintInFile(list_tree *tr, FILE *out, unsigned char *arr, out_buf *c);
void tree_to_b(list_tree *head, FILE *out, unsigned char *arr);
void mkcode(list_tree *h, int i, char *c, codes *code);
void crCode(list_tree *h, codes *code);
int d_main(FILE *out, FILE *info, codes *cd, out_buf *b);
void compress(FILE *out, codes *cd, out_buf *b, size_t l, FILE *in, unsigned int *crc);
void byte_to_bit(out_buf *b, unsigned char bit, FILE *out, unsigned int *crc);
void create_tree(list_tree *h, unsigned char *tib);
void unpress(list_tree *h, FILE *out, size_t len, FILE *info, unsigned int *crc, size_t size);
int counter;
unsigned char buff[SZ];
#endif // !PROG_H
	