/* display no. of lines, words and characters in input */

%{
int nchar, nword, nline;
%}

%%

\n 		{ nline++; nchar++; }
[^ \t\n]+ 	{ nword++, nchar += yyleng; }
. 		{ nchar++; }

%%

void main()
{
	yylex();
	printf("No. of characters: %d\nNo. of words: %d\nNo. of lines: %d\n", nchar, nword, nline);
}
