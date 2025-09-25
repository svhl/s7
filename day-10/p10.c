// intermediate code generation

#include <stdio.h>
#include <string.h>

int prec(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    
    if (op == '+' || op == '-')
    {
        return 1;
    }
    
    return 0;
}

int main()
{
    char expr[100], temp = 'Z', code[10][20]; 
    int n = 0;
    scanf("%s", expr);
    char lhs = expr[0], rhs[100]; 
    strcpy(rhs, expr + 2);

    while (1)
    {
        int i, max = -1, pos = -1;
        
        for (i = 0; rhs[i]; i++)
        {
            if (strchr("+-*/", rhs[i]) && prec(rhs[i]) > max)
            {
                max = prec(rhs[i]), pos = i;
            }
        }
        
        if (pos == -1)
        {
            break;
        }
        
        sprintf(code[n++], "%c=%c%c%c", temp, rhs[pos - 1], rhs[pos], rhs[pos + 1]);
        rhs[pos - 1] = temp--; 
        strcpy(rhs + pos, rhs + pos + 2);
    }

    sprintf(code[n++], "%c=%c", lhs, rhs[0]);
    
    for (int i = 0; i < n; i++)
    {
        puts(code[i]);
    }
}
