#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char productions[MAX][MAX];
char first[MAX][MAX];
int n; // number of productions

// Function to check if symbol is a terminal
int isTerminal(char c) {
    return !isupper(c) && c != '#' && c != '\0';
}

// Function to add a symbol to FIRST set (avoiding duplicates)
void addToFirst(int i, char c) {
    int k;
    for (k = 0; first[i][k] != '\0'; k++) {
        if (first[i][k] == c) return; // avoid duplicate
    }
    first[i][k] = c;
    first[i][k+1] = '\0';
}

// Recursive function to find FIRST of a non-terminal
void findFirst(int i) {
    char *rule = productions[i];
    char nt = rule[0]; // non-terminal
    char *rhs = strchr(rule, '>') + 1; // RHS starts after "A->"
    char body[50];
    int pos = 0;

    for (int j = 0; ; j++) {
        if (rhs[j] == '|' || rhs[j] == '\0') {
            body[pos] = '\0'; // end of one body
            pos = 0;

            // Process this body
            if (body[0] == '#') { // epsilon directly
                addToFirst(i, '#');
            } else {
                int k, allEpsilon = 1; // assume all can go to epsilon
                for (k = 0; body[k] != '\0'; k++) {
                    char symbol = body[k];
                    if (isTerminal(symbol)) {
                        addToFirst(i, symbol);
                        allEpsilon = 0;
                        break;
                    } else { // Non-terminal
                        for (int m = 0; m < n; m++) {
                            if (productions[m][0] == symbol) {
                                if (first[m][0] == '\0') findFirst(m);
                                int hasEps = 0;
                                for (int x = 0; first[m][x] != '\0'; x++) {
                                    if (first[m][x] == '#') hasEps = 1;
                                    else addToFirst(i, first[m][x]);
                                }
                                if (!hasEps) {
                                    allEpsilon = 0;
                                    goto nextBody; // stop checking further symbols
                                }
                            }
                        }
                    }
                }
                if (allEpsilon) addToFirst(i, '#'); // entire body -> epsilon
            }
        nextBody: ;
        if (rhs[j] == '\0') break;
        } else {
            body[pos++] = rhs[j];
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., S->AB|#, A->a|#):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
        first[i][0] = '\0'; // Initialize FIRST set
    }

    for (int i = 0; i < n; i++) {
        if (first[i][0] == '\0') findFirst(i);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = { ", productions[i][0]);
        for (int j = 0; first[i][j] != '\0'; j++) {
            if (first[i][j] == '#') printf("ε "); // pretty print epsilon
            else printf("%c ", first[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
