/* find no. of vowels and consonants in input */

%{
int nvowel = 0, ncons = 0;
%}

%%

[aeiouAEIOU]				{ nvowel++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]	{ ncons++; }
.|\n					{ }

%%

int main(void)
{
    yylex();
    printf("No. of vowels: %d\nNo. of consonants: %d\n", nvowel, ncons);
}
