#include "apc.h"

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Arguments count shoud be exactly four");
        return FAILURE;
    }

    int i = 0;
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("First number should contain only digits\n");
            return FAILURE;
        }
    }

    for (int i = 0; argv[3][i] != '\0'; i++)
    {
        if (!isdigit(argv[3][i]))
        {
            printf("Second number should contain only digits\n");
            return FAILURE;
        }
    }

    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != '*' && argv[2][0] != '/')
    {
        printf("Invalid operator. Use +, -, *, or /\n");
        return FAILURE;
    }

    printf("First number: %s\n", argv[1]);
    printf("Operator: %c\n", argv[2][0]);
    printf("Second number: %s\n", argv[3]);

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *res_head = NULL, *res_tail = NULL;

    for (i = 0; argv[1][i] != '\0'; i++)
    {
        int digit = argv[1][i] - '0';
        insert_at_end(&head1, &tail1, digit);
    }

    for (i = 0; argv[3][i] != '\0'; i++)
    {
        int digit = argv[3][i] - '0';
        insert_at_end(&head2, &tail2, digit);
    }

    int is_negative = 0;

    switch (argv[2][0])
    {
    case '+':
        add(&head1, &tail1, &head2, &tail2, &res_head, &res_tail);
        break;

    case '-':
        is_negative = compare(&head1, &head2);
        sub(&head1, &tail1, &head2, &tail2, &res_head, &res_tail);
        break;
    }

    printf("Result: ");
    if (is_negative)
    {
        printf("-");
    }
    print_list(res_head);
    printf("\n");

    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&res_head, &res_tail);

    return SUCCESS;
}