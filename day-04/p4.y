/* calculator */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

int result;

extern int yy_scan_string(const char *str);
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

input:
	expr '\n'	{ result = $1; }
	;

expr:
	expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{
	
	if ($3 == 0)
	{
		yyerror("Division by zero");
		YYABORT;
	}
	
	$$ = $1 / $3;
			}
	| '(' expr ')'	{ $$ = $2; }
	| NUM		{ $$ = $1; }
	;

%%

int main()
{
	char input[100];
	printf("Enter an arithmetic expression:\n");

	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		printf("Error reading input.\n");
		return 1;
	}

	yy_scan_string(input);

	if (yyparse())
	{
		printf("Invalid\n");
	}
	
	else
	{
		printf("Result: %d\n", result);
	}

	return 0;
}


void yyerror(const char *s)
{
	fprintf(stderr, "Error: %s\n", s);
}