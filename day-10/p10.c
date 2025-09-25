// intermediate code generation

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char result;
    char op1;
    char op2;
    char operator;
} Code;

int precedence(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }

    else if (op == '+' || op == '-')
    {
        return 1;
    }

    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void main()
{
    char expr[100], rhs[100];
    Code codes[100];
    int codeIndex = 0;
    char tempVar = 'Z';

    printf("Enter the expression: ");
    scanf("%s", expr);

    char lhs = expr[0];
    strcpy(rhs, expr + 2);

    while (1)
    {
        int i, found = 0;
        int maxPrecedence = -1;
        int opIndex = -1;

        for (i = 0; rhs[i] != '\0'; i++)
        {
            if (isOperator(rhs[i]))
            {
                int p = precedence(rhs[i]);
                if (p > maxPrecedence)
                {
                    maxPrecedence = p;
                    opIndex = i;
                }
            }
        }

        if (opIndex == -1)
        {
            break;
        }

        char op = rhs[opIndex];
        char left = rhs[opIndex - 1];
        char right = rhs[opIndex + 1];
        codes[codeIndex].result = tempVar;
        codes[codeIndex].op1 = left;
        codes[codeIndex].op2 = right;
        codes[codeIndex].operator = op;
        codeIndex++;
        char newRHS[100];
        int k = 0;

        for (i = 0; i < opIndex - 1; i++)
        {
            newRHS[k++] = rhs[i];
        }

        newRHS[k++] = tempVar;

        for (i = opIndex + 2; rhs[i] != '\0'; i++)
        {
            newRHS[k++] = rhs[i];
        }

        newRHS[k] = '\0';
        strcpy(rhs, newRHS);
        tempVar--;
    }

    codes[codeIndex].result = lhs;
    codes[codeIndex].op1 = rhs[0];
    codes[codeIndex].op2 = '\0';
    codes[codeIndex].operator = '=';

    printf("\nIntermediate code:\n\n");

    for (int i = 0; i <= codeIndex; i++)
    {
        if (codes[i].operator == '=')
        {
            printf("%c=%c\n", codes[i].result, codes[i].op1);
        }
        
        else
        {
            printf("%c=%c%c%c\n", codes[i].result, codes[i].op1, codes[i].operator, codes[i].op2);
        }
    }
}