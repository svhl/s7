/* calculator */

%{
#include "y.tab.h"
%}

%%

[0-9]+		{ yylval = atoi(yytext); return NUM; }
[ \t\r]		{ }
"\n"		{ return '\n'; }
"("		{ return '('; }
")"		{ return ')'; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
.		{ return 0; }

%%

int yywrap()
{
	return 1;
}