#include "apc.h"

void print_list(Dlist *head)
{
    Dlist *temp = head;
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void free_list(Dlist **head, Dlist **tail)
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
}

void insert_at_end(Dlist **head, Dlist **tail, int data)
{
    Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
    if (!new_node)
        return;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = *tail;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

void insert_at_beginning(Dlist **head, Dlist **tail, int data)
{
    Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
    if (!new_node)
        return;

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = *head;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*head)->prev = new_node;
        *head = new_node;
    }
}

int compare(Dlist **head1, Dlist **head2)
{
    int len1 = 0, len2 = 0;
    Dlist *t1 = *head1, *t2 = *head2;

    while (t1)
    {
        len1++;
        t1 = t1->next;
    }
    while (t2)
    {
        len2++;
        t2 = t2->next;
    }

    if (len1 < len2)
    {
        return 1;
    }

    else if (len1 > len2)
    {
        return 0;
    }

    // (len1 == len2)
    else
    {
        t1 = *head1;
        t2 = *head2;

        while (t1 && t2)
        {
            if (t1->data < t2->data)
            {
                return 1;
            }
            else if (t1->data > t2->data)
            {
                return 0;
            }
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    // Both lenghts are same and digits are also same
    return 0;
}

int add(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int carry = 0;
    int sum = 0;
    int digit1, digit2;

    while (temp1 != NULL || temp2 != NULL || carry)
    {
        digit1 = (temp1 != NULL) ? temp1->data : 0;
        digit2 = (temp2 != NULL) ? temp2->data : 0;

        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        insert_at_beginning(res_head, res_tail, sum);

        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
        }
        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    return SUCCESS;
}

int sub(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{
    // Compare numbers
    int negative = compare(head1, head2);

    // swap if num1 < num2
    if (negative)
    {
        Dlist *temp_head = *head1;
        Dlist *temp_tail = *tail1;

        *head1 = *head2;
        *tail1 = *tail2;

        *head2 = temp_head;
        *tail2 = temp_tail;
    }

    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int borrow = 0;
    int diff = 0;
    int digit1, digit2;

    while (temp1 != NULL || temp2 != NULL)
    {
        digit1 = (temp1 != NULL) ? temp1->data : 0;
        digit2 = (temp2 != NULL) ? temp2->data : 0;

        diff = digit1 - digit2 - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insert_at_beginning(res_head, res_tail, diff);

        if (temp1 != NULL)
            temp1 = temp1->prev;

        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    while (*res_head != NULL && (*res_head)->data == 0 && (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;
        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;
        free(temp);
    }

    if (*res_head == NULL)
    {
        insert_at_beginning(res_head, res_tail, 0);
    }

    return SUCCESS;
}
