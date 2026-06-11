#include "header.h"

extern int negative;
extern int sign1;
extern int sign2;

/* Function to read and validate command line arguments */
int read_and_validate(char *argv[])
{
    int i = 0;
    while (argv[1][i] != '\0')
    {
        if (!((argv[1][i] >= '0' && argv[1][i] <= '9') || argv[1][0] == '+' || argv[1][0] == '-'))
        {
            printf("Error : First number mentioned is not a digit!!!\n");
            return FAILURE;
        }
        i++;
    }

    i = 0;
    if (!((argv[2][0] == '+') || (argv[2][0] == '-') || (argv[2][0] == 'x') || (argv[2][0] == '/')))
    {
        printf("Error : Operator mentioned is not correct!!!\n");
        return FAILURE;
    }

    while (argv[3][i] != '\0')
    {
        if (!((argv[3][i] >= '0' && argv[3][i] <= '9') || argv[3][0] == '+' || argv[3][0] == '-'))
        {
            printf("Error : Second number mentioned is not a digit!!!\n");
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}

/* Inserting the elements to lists */
int insert_element(Dlist **head, Dlist **tail, char argv[], int *sign)
{
    int i = 0;
    *sign = 1;
    if (argv[i] == '+')
    {
        i++;
    }

    if (argv[i] == '-')
    {
        *sign = -1;
        i++;
    }

    while (argv[i] != '\0')
    {
        int num = argv[i] - '0';
        if (insert_at_last(head, tail, num) == FAILURE)
            return FAILURE;
        i++;
    }
    return SUCCESS;
}

/* Function to insert the data at the last of the list */
int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    if ((*head == NULL) || (*tail == NULL))
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        (*tail)->next = new;
        new->prev = *tail;
        *tail = new;
    }
    return SUCCESS;
}

/* Function to insert the data at the first of the list */
int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    if ((*head == NULL) || (*tail == NULL))
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        (*head)->prev = new;
        new->next = *head;
        *head = new;
    }
    return SUCCESS;
}

/* Function to print the lists */
void Print_list_element(Dlist *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        printf("RESULT -> ");
        if (negative == 1)
            printf("-");

        while (head)
        {
            /* Printing the list */
            printf("%d", head->data);
            head = head->next;
        }
        printf("\n");
    }
}

/* Function to delete the list */
int Delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}

/* Function to comare to lists */
int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    /* Count length of both lists */
    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    /* Compare by length */
    if (len1 > len2)
        return 1;
    else if (len1 < len2)
        return -1;

    temp1 = head1;
    temp2 = head2;
    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        else if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0;
}

/* Function to validate the operation */
void operation_validation(char *operator, Dlist **head1, Dlist **head2)
{
    if (*operator == '+')
    {
        if (sign1 == -1 && sign2 == -1)
        {
            negative = 1;
            *operator = '+';
        }
        else if (sign1 == -1 && sign2 == 1)
        {
            if (compare(*head2, *head1) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else if (sign1 == 1 && sign2 == -1)
        {
            if (compare(*head1, *head2) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else
        {
            negative = 0;
            *operator = '+';
        }
    }
    else if (*operator == '-')
    {
        if (sign1 == 1 && sign2 == 1)
        {
            if (compare(*head1, *head2) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else if (sign1 == 1 && sign2 == -1)
        {
            *operator = '+';
            negative = 0;
        }
        else if (sign1 == -1 && sign2 == 1)
        {
            *operator = '+';
            negative = 1;
        }
        else if (sign1 == -1 && sign2 == -1)
        {
            if (compare(*head2, *head1) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
    }
    else if (*operator == '/' || *operator == 'x')
    {
        if ((sign1 == 1 && sign2 == 1) || (sign1 == -1 && sign2 == -1))
        {
            negative = 0;
        }
        else
        {
            negative = 1;
        }
    }
}

/* Function to remove the leading zeros */
void remove_leading_zeros(Dlist **head)
{
    while (*head && ((*head)->data == 0) && ((*head)->next) != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        if (*head)
            (*head)->prev = NULL;
        free(temp);
    }
}

/* Function to copy one list to another list */
void copy_list(Dlist *src_head, Dlist **dest_head, Dlist **dest_tail)
{
    while (src_head != NULL)
    {
        Dlist *new = create_node(src_head->data);

        if (*dest_head == NULL)
        {
            *dest_head = new;
            *dest_tail = new;
        }
        else
        {
            (*dest_tail)->next = new;
            new->prev = *dest_tail; // maintain prev link
            *dest_tail = new;
        }

        src_head = src_head->next;
    }
}

/*Function to create node */
Dlist *create_node(int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return NULL;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}