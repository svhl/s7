// display no. of lines, words and characters in input

%{
	int nchar, nword, nline;
%}

%%

\n 		{ nline++; nchar++; }
[^ \t\n]+ 	{ nword++, nchar += yyleng; }
. 		{ nchar++; }

%%

int main(void)
{
	yylex();
	printf("No. of characters: %d\nNo. of words: %d\nNo. of lines: %d\n", nchar, nword, nline);
	return 0;
}
