/* recognize a valid identifier */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token IDENTIFIER

%%

start:
	IDENTIFIER;

%%

int main()
{
	printf("Enter an identifier:\n");

	if (yyparse())
	{
		printf("Invalid\n");
	}

	else
	{
		printf("Valid\n");
	}

	return 0;
}

void yyerror(const char *s)
{
}