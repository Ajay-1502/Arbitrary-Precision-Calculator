#include "header.h"

/* Function to Subtraction of input list */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Checking for empty lists */
    if (*head1 == NULL && *head2 == NULL)
        return FAILURE;

    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    /* Checking if list 2 is greater than list1 */
    int cmp = compare(*head1, *head2);

    if (cmp == 0)
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

    /* Swapping the pointers */
    if (cmp < 0)
    {
        Dlist *tmpHead = *head1;
        Dlist *tmpTail = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = tmpHead;
        *tail2 = tmpTail;
        temp1 = *tail1;
        temp2 = *tail2;
    }

    int borrow = 0, result = 0;

    /* Running the loop till both the lists reach the end */
    while (temp1 != NULL || temp2 != NULL)
    {

        int val1 = (temp1) ? temp1->data : 0;
        int val2 = (temp2) ? temp2->data : 0;

        /* Storing the difference in the result variable */
        result = val1 - val2 - borrow;

        if (result < 0)
        {
            result += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        /* Storing the result at first of the result */
        insert_at_first(headR, tailR, result);

        if (temp1)
            temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }
    remove_leading_zeros(headR);
    return SUCCESS;
}