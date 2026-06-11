#include "header.h"

/* Function for multiplication */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp2 = *tail2;
    int count = 0;

    *headR = NULL;
    *tailR = NULL;
    Dlist *headR2 = NULL;
    Dlist *tailR2 = NULL;

    /* Running the loop till the second list reaches the end */
    while (temp2 != NULL)
    {
        /* Taking one by one number( node values ) from the list to for multiplication */
        int val1 = temp2->data;
        Dlist *temp1 = *tail1;

        Dlist *headR1 = NULL;
        Dlist *tailR1 = NULL;

        int carry = 0;

        /* Running the loop till the first list reaches the end */
        while (temp1 != NULL)
        {
            int val2 = temp1->data;
            int res = val1 * val2 + carry;

            int rem = res % 10;
            carry = res / 10;

            /* Storing the result in temporary result list */
            insert_at_first(&headR1, &tailR1, rem);

            temp1 = temp1->prev;
        }

        if (carry)
        {
            insert_at_first(&headR1, &tailR1, carry);
        }

        for (int i = 0; i < count; i++)
        {
            insert_at_last(&headR1, &tailR1, 0);
        }

        /* For first insertion in the main result list */
        if (*headR == NULL)
        {
            *headR = headR1;
            *tailR = tailR1;
            headR1 = NULL;
            tailR1 = NULL;
        }
        else /* Insertion of the remaining values in the result */
        {
            addition(headR, tailR, &headR1, &tailR1, &headR2, &tailR2);
            Delete_list(headR, tailR);
            *headR = headR2;
            *tailR = tailR2;
            Delete_list(&headR1, &tailR2);
            headR2 = NULL;
            tailR2 = NULL;
        }
        count++;
        temp2 = temp2->prev;
    }

    return SUCCESS;
}