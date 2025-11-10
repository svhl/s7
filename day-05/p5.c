// nfa to dfa

#include <stdio.h>
#include <string.h>
#include <ctype.h> 

void sortState(char *s)
{
	int len = strlen(s);

	for (int i = 0; i < len; i += 2)
	{
		for (int j = i + 2; j < len; j += 2)
		{
			if (s[i + 1] > s[j + 1])
			{
				char t1 = s[i + 1];
				s[i + 1] = s[j + 1];
				s[j + 1] = t1;
			}
		}
	}
}

void main()
{
	int n, s, nfa[10][10][10];
	char state[20][20], dfa[20][20][20];
	int ndfa = 1, i, j, k, l;
	printf("Enter no. of states: ");
	scanf("%d", &n);
	printf("Enter no. of input symbols: ");
	scanf("%d", &s);

	for (k = 1; k <= s; k++)
	{
		printf("Enter NFA matrix for input %d:\n", k);

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				scanf("%d", &nfa[k][i][j]);
			}
		}
	}

	strcpy(state[0], "q0");
	printf("\n\t");

	for (i = 1; i <= s; i++)
	{
		printf("Input %d\t", i);
	}

	printf("\n");

	for (i = 0; i < ndfa; i++)
	{
		printf("%-8s", state[i]);

		for (k = 1; k <= s; k++)
		{
			char ns[30] = "";

			for (j = 0; j < strlen(state[i]); j++)
			{
				if (state[i][j] == 'q' && isdigit(state[i][j + 1]))
				{
					int x = state[i][j + 1] - '0';

					for (l = 0; l < n; l++)
					{
						if (nfa[k][x][l] == 1)
						{
							char t[5];
							sprintf(t, "q%d", l);

							if (!strstr(ns, t))
							{
								strcat(ns, t);
							}
						}
					}
				}
			}

			if (strlen(ns) == 0)
			{
				strcpy(ns, "-");
			}

			sortState(ns);
			strcpy(dfa[i][k], ns);
			printf("%-10s", ns);
			int found = 0;

			for (j = 0; j < ndfa; j++)
			{
				if (strcmp(state[j], ns) == 0)
				{
					found = 1;
				}
			}

			if (!found && strcmp(ns, "-") != 0)
			{
				strcpy(state[ndfa++], ns);
			}
		}

		printf("\n");
	}
}
