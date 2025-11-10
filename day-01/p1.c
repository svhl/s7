// lexical analyzer

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char printed[100][20];
int printedCount = 0;

int alreadyPrinted(char *word)
{
	for (int i = 0; i < printedCount; i++)
	{
		if (strcmp(printed[i], word) == 0)
			return 1;
	}
	return 0;
}

void addPrinted(char *word)
{
	strcpy(printed[printedCount++], word);
}

int isKeyword(char word[])
{
	char keywords[5][10] = {"int", "float", "if", "else", "while"};

	for (int i = 0; i < 5; i++)
	{
		if (strcmp(word, keywords[i]) == 0)
		{
			return 1;
		}
	}

	return 0;
}

void main()
{
	FILE *fp;
	char c, word[20];
	int i;
	fp = fopen("input.c", "r");

	if (fp == NULL)
	{
		printf("File not found");
		return;
	}

	while ((c = fgetc(fp)) != EOF)
	{
		if (strchr(" \n\t", c))
		{
			continue;
		}

		if (c == '/')
		{
			char next = fgetc(fp);

			if (next == '/')
			{
				while ((c = fgetc(fp)) != '\n' && c != EOF);
				{
					continue;
				}
			}
		}

		if (isalpha(c))
		{
			i = 0;
			word[i++] = c;

			while (isalnum(c = fgetc(fp)))
			{
				word[i++] = c;
			}

			word[i] = '\0';
			fseek(fp, -1, SEEK_CUR);

			if (isKeyword(word))
			{
				if (!alreadyPrinted(word))
				{
					printf("Keyword: %s\n", word);
					addPrinted(word);
				}
			}

			else
			{
				if (!alreadyPrinted(word))
				{
					printf("Identifier: %s\n", word);
					addPrinted(word);
				}
			}
		}

		else if (isdigit(c))
		{
			char num[5] = {c, '\0'};

			if (!alreadyPrinted(num))
			{
				printf("Number: %c\n", c);
				addPrinted(num);
			}
		}

		else if (strchr("=+-*/;(){}", c))
		{
			char sym[2] = {c, '\0'};

			if (!alreadyPrinted(sym))
			{
				printf("Symbol: %c\n", c);
				addPrinted(sym);
			}
		}
	}

	fclose(fp);
}
