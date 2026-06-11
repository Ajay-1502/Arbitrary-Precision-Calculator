#include "header.h"

/* Function to perform addition */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Checking for empty list */
    if (*head1 == NULL && *head2 == NULL)
        return FAILURE;

    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int carry = 0, result = 0;

    /* Running the loop till both the input list reach "NUL" */
    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 != NULL && temp2 == NULL)
        {

            result = temp1->data + 0 + carry;
        }
        else if (temp1 == NULL && temp2 != NULL)
        {

            result = temp2->data + 0 + carry;
        }
        else
        {
            /* Storing the result of addition in one variable */
            result = temp1->data + temp2->data + carry;
        }

        carry = 0;
        if (result > 9)
        {
            carry = result / 10;
            result = result % 10;
        }

        /* Storing the result from the first position */
        insert_at_first(headR, tailR, result);

        if (temp1)
            temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }

    /* If the carry is present after the first of the result list */
    if (carry)
        insert_at_first(headR, tailR, carry);

    return SUCCESS;
}