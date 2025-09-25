// constant propagation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    char var[100];
    int value;
} Constant;

typedef struct
{
    char var[100];
    char expr[100];
} Assignment;

Constant constants[100];
Assignment assignments[100];
Assignment direct_assignments[100];
int constant_count = 0, assignment_count = 0, direct_assignment_count = 0;

int get_constant_value(const char *var_name)
{
    for (int i = 0; i < constant_count; i++)
    {
        if (strcmp(constants[i].var, var_name) == 0)
        {
            return constants[i].value;
        }
    }
    return -1;
}

void add_constant(const char *var_name, int value)
{
    strcpy(constants[constant_count].var, var_name);
    constants[constant_count].value = value;
    constant_count++;
}

void propagate_constant_in_expr(char *expr)
{
    char result[100];
    int i = 0, j = 0;

    while (expr[i] != '\0')
    {
        if (isalpha(expr[i]))
        {
            char var_name[100];
            int k = 0;

            while (isalpha(expr[i]) || isdigit(expr[i]))
            {
                var_name[k++] = expr[i++];
            }

            var_name[k] = '\0';
            int value = get_constant_value(var_name);

            if (value != -1)
            {
                j += sprintf(&result[j], "%d", value);
            }
            
            else
            {
                j += sprintf(&result[j], "%s", var_name);
            }
        }
        
        else
        {
            result[j++] = expr[i++];
        }
    }

    result[j] = '\0';
    strcpy(expr, result);
}

void main()
{
    char line[100];
    printf("Enter assignments. Press Enter on an empty line to finish:\n");

    while (1)
    {
        fgets(line, 100, stdin);
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            break;
        }

        char var_name[100];
        int value;

        if (sscanf(line, "%s = %d", var_name, &value) == 2)
        {
            add_constant(var_name, value);
            strcpy(direct_assignments[direct_assignment_count].var, var_name);
            sprintf(direct_assignments[direct_assignment_count].expr, "%d", value);
            direct_assignment_count++;
        }
        
        else
        {
            char var_name[100];
            char expr[100];
            sscanf(line, "%s = %[^\n]", var_name, expr);
            strcpy(assignments[assignment_count].var, var_name);
            strcpy(assignments[assignment_count].expr, expr);
            assignment_count++;
        }
    }

    printf("\nAfter constant propagation:\n");

    for (int i = 0; i < direct_assignment_count; i++)
    {
        printf("%s = %s\n", direct_assignments[i].var, direct_assignments[i].expr);
    }

    for (int i = 0; i < assignment_count; i++)
    {
        char expr[100];
        strcpy(expr, assignments[i].expr);
        propagate_constant_in_expr(expr);
        printf("%s = %s\n", assignments[i].var, expr);
    }
}
