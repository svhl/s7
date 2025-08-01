/* recognize a valid arithmetic expression */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUM
%token VAR
%left '+' '-'
%left '*' '/'

%%

expr:
	expr '+' expr	{ $$ = 1; }
	| expr '-' expr	{ $$ = 1; }
	| expr '*' expr	{ $$ = 1; }
	| expr '/' expr	{ $$ = 1; }
	| '(' expr ')'	{ $$ = 1; }
	| NUM		{ $$ = 1; }
	| VAR		{ $$ = 1; }
	;

%%

int main()
{
	printf("Enter an arithmetic expression:\n");
	
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
	fprintf(stderr, "Error: %s\n", s);
}
