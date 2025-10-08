// compiler backend

#include <stdio.h>
#include <string.h>

int regCount = 0;

void generate(char result[], char op1[], char op[], char op2[])
{
    printf("MOV %s, R%d\n", op1, regCount);

    if (strcmp(op, "*") == 0)
    {
        printf("MUL %s, R%d\n", op2, regCount);
    }

    else if (strcmp(op, "+") == 0)
    {
        printf("ADD %s, R%d\n", op2, regCount);
    }

    else if (strcmp(op, "-") == 0)
    {
        printf("SUB %s, R%d\n", op2, regCount);
    }

    printf("MOV R%d, %s\n\n", regCount, result);
    regCount++;
}

void main()
{
    char line[50], result[10], op1[10], op[5], op2[10];
    printf("Enter TAC (end with exit):\n");

    while (1)
    {
        fgets(line, sizeof(line), stdin);
        if (strncmp(line, "exit", 4) == 0) break;
        sscanf(line, "%s = %s %s %s", result, op1, op, op2);
        generate(result, op1, op, op2);
    }
}

