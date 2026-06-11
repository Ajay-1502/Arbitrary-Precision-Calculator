#include "header.h"

#if 1
#include "header.h"

/* Function for Division */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **Q_head, Dlist **Q_tail)
{
    /* Removing the tailing zeros from both the lists */
    /*
       while(*head1 != NULL && (*head1) -> data == 0)
     *head1 = (*head1) -> next;

     while(*head2 != NULL && (*head2) -> data == 0)
     *head2 = (*head2) -> next;
     */
    remove_leading_zeros(head1);
    remove_leading_zeros(head2);

    /* If both lists reaches NULL means both input lists are Zero */
    if (*head1 == NULL && *head2 == NULL)
    {
        printf("Error : Division of Zero by Zero is not possible!!\n");
        return FAILURE;
    }

    /* If list 1 reaches NULL this means first list is zero so the division result will be zero */
    if (*head1 == NULL)
    {
        insert_at_first(Q_head, Q_tail, 0);
        return SUCCESS;
    }

    /* If list 2 reaches NULL this means second list is zero leading to division by zero error */
    if (*head2 == NULL)
    {
        printf("Error : Division by Zero is not possible!!\n");
        return FAILURE;
    }

    /* Dividend < Divisor → quotient = 0 */
    if (compare(*head1, *head2) < 0)
    {
        insert_at_first(Q_head, Q_tail, 0);
        return SUCCESS;
    }

    Dlist *dividend_h = NULL, *dividend_t = NULL;
    Dlist *divisor_h = NULL, *divisor_t = NULL;
    copy_list(*head1, &dividend_h, &dividend_t);
    copy_list(*head2, &divisor_h, &divisor_t);

    /* quotient = 0 */
    insert_at_first(Q_head, Q_tail, 0);

    while (dividend_h != NULL && compare(dividend_h, divisor_h) >= 0)
    {
        /* temp_divisor = divisor */
        Dlist *temp_div_h = NULL, *temp_div_t = NULL;
        copy_list(divisor_h, &temp_div_h, &temp_div_t);

        /* temp_mul = 1  (power of 2 multiplier) */
        Dlist *temp_mul_h = NULL, *temp_mul_t = NULL;
        insert_at_first(&temp_mul_h, &temp_mul_t, 1);

        /* Find largest (divisor * 2^k ≤ dividend) */
        while (1)
        {
            Dlist *next_h = NULL, *next_t = NULL;
            copy_list(temp_div_h, &next_h, &next_t);
            multiply_by_2(&next_h, &next_t);

            if (compare(next_h, dividend_h) > 0)
            {
                Delete_list(&next_h, &next_t);
                break;
            }

            /* Accept doubling */
            Delete_list(&temp_div_h, &temp_div_t);
            temp_div_h = next_h;
            temp_div_t = next_t;

            multiply_by_2(&temp_mul_h, &temp_mul_t);
        }

        /* dividend -= temp_div */
        Dlist *res_h = NULL, *res_t = NULL;
        subtraction(&dividend_h, &dividend_t, &temp_div_h, &temp_div_t, &res_h, &res_t);
        Delete_list(&dividend_h, &dividend_t);
        dividend_h = res_h;
        dividend_t = res_t;
        remove_leading_zeros(&dividend_h);

        /* quotient += temp_mul */
        Dlist *new_q_h = NULL, *new_q_t = NULL;
        addition(Q_head, Q_tail, &temp_mul_h, &temp_mul_t, &new_q_h, &new_q_t);
        Delete_list(Q_head, Q_tail);
        *Q_head = new_q_h;
        *Q_tail = new_q_t;

        Delete_list(&temp_div_h, &temp_div_t);
        Delete_list(&temp_mul_h, &temp_mul_t);
    }

    remove_leading_zeros(Q_head);
    return SUCCESS;
}
#endif

/* Function equivalent to num << 2 */
void multiply_by_2(Dlist **head, Dlist **tail)
{
    Dlist *temp = *tail;
    int carry = 0;

    while (temp)
    {
        int val = temp->data * 2 + carry;
        temp->data = val % 10;
        carry = val / 10;
        temp = temp->prev;
    }
    if (carry)
        insert_at_first(head, tail, carry);
}