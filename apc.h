#ifndef APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
} Dlist;

void print_list(Dlist *head);
void free_list(Dlist **head, Dlist **tail);
void insert_at_end(Dlist **head, Dlist **tail, int data);
void insert_at_beginning(Dlist **head, Dlist **tail, int data);
int compare(Dlist **head1, Dlist **head2);
int add(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail);
int sub(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail);

#endif
