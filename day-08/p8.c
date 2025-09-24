// shift reduce parser

#include <stdio.h>
#include <string.h>

char stack[100], input[100];
char productions[20][20];
int n, top = -1, ip = 0;

void printStep(const char *action) {
    printf("%-20s %-20s %-20s\n", stack, input + ip, action);
}

int reduce()
{
    for (int i = 0; i < n; i++)
    {
        char lhs = productions[i][0];
        char *rhs = productions[i] + 2;
        int len = strlen(rhs);

        if (top + 1 >= len && strncmp(stack + top - len + 1, rhs, len) == 0)
        {
            top = top - len + 1;
            stack[top] = lhs;
            stack[top + 1] = '\0';
            char msg[40];
            sprintf(msg, "Reduce by %s", productions[i]);
            printStep(msg);
            return 1;
        }
    }
    return 0;
}

void main()
{
    printf("Enter no. of productions: ");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", productions[i]);
    }

    printf("Enter the input string: ");
    scanf("%s", input);

    printf("%-20s %-20s %-20s\n", "Stack", "Input", "Action");

    while (1)
    {
        if (stack[0] == productions[0][0] && stack[1] == '\0' && input[ip] == '\0')
        {
            printf("String accepted.\n");
            break;
        }

        if (!reduce())
        {
            if (input[ip] == '\0')
            {
                printf("String rejected.\n");
                break;
            }
            
            stack[++top] = input[ip++];
            stack[top + 1] = '\0';
            printStep("Shift");
        }
    }
}