// constant propagation

#include <stdio.h>
#include <string.h>

char vars[10][10];
int vals[10];
int count = 0;

int getval(char *v)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(vars[i], v) == 0)
        {
            return vals[i];
        }
    }

    return -9999;
}

void main()
{
    char line[50], var[10], expr[50];
    int val;
    printf("Enter assignments (exit to stop):\n");

    while (1)
    {
        fgets(line, sizeof(line), stdin);

        if (strcmp(line, "exit\n") == 0)
        {
            break;
        }

        if (sscanf(line, "%s = %d", var, &val) == 2)
        {
            strcpy(vars[count], var);
            vals[count] = val;
            count++;
        }
        
        else if (sscanf(line, "%s = %[^\n]", var, expr) == 2)
        {
            printf("%s = ", var);
            char *tok = strtok(expr, " ");

            while (tok != NULL)
            {
                int v = getval(tok);

                if (v != -9999)
                {
                    printf("%d ", v);
                }

                else
                {
                    printf("%s ", tok);
                }

                tok = strtok(NULL, " ");
            }
            
            printf("\n");
        }
    }
}
