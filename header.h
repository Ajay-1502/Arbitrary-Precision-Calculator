#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
} Dlist;

int read_and_validate(char *argv[]);

/* Include the prototypes here */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Inserting elements in Linked list
int insert_element(Dlist **, Dlist **, char *, int *);

// Insertion elements at last.
int insert_at_last(Dlist **, Dlist **, int);

// Insertion elements at first.
int insert_at_first(Dlist **, Dlist **, int);

// Print List elements
void Print_list_element(Dlist *head);

// Delete List
int Delete_list(Dlist **head, Dlist **tail);

// COMPARING LIST
int compare(Dlist *head1, Dlist *head2);
void Div(Dlist **h1, Dlist **t1, Dlist **h2, Dlist **t2, Dlist **rh, Dlist **rt);

Dlist *get_tail(Dlist *head);

void remove_leading_zeros_head(Dlist **head, Dlist **tail);

void remove_leading_zeros(Dlist **head);

int multiply_single_digit(Dlist *numHead, Dlist *numTail, int d, Dlist **resHead, Dlist **resTail);

void operation_validation(char *operator, Dlist ** head1, Dlist **head2);

Dlist *create_node(int data);

void copy_list(Dlist *src_head, Dlist **dest_head, Dlist **dest_tail);

void add_one(Dlist **head, Dlist **tail);

void multiply_by_2(Dlist **head, Dlist **tail);

void divide_by_2(Dlist **head, Dlist **tail);

#endif