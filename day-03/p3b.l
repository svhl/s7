/* recognize a valid identifier */

%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*	{ return IDENTIFIER; }
[ \t\r\n]		{ }
.			{ return 0; }

%%

int yywrap()
{
	return 1;
}