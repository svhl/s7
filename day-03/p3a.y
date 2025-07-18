// recognize a valid arithmetic expression

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int yylex(void);
void yyerror(const char *s);
%}

%token NUM
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
}