#ifndef PROG_H
#define PROG_H
#include <stdio.h> 
#include <string.h> 
#include <malloc.h> 
typedef struct list {
	struct list *next;
	int val;
} list;
void Insert(int a, struct list **head);
void printlist(struct list *head, char *out);
void Freelist(struct list *head);
#define G 5
#endif
