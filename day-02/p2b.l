/* check valid email address */

%{
int flag = 0;
%}

%%

[0-9A-Za-z.-_]+@[A-Za-z.-]+\.[A-Za-z]	{ flag = 1; }
.|\n					{ }

%%

void main()
{
    yylex();

    if (flag == 1)
    {
        printf("Valid email address\n");
    }
    
    else
    {
        printf("Invalid email address\n");
    }
}

