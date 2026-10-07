#include <stdio.h>

int n, m;                /* n = number of states, m = number of symbols */
int closure[20][20];     /* closure[i][j] = 1: j is in e-closure of i */
int move[20][4][20];     /* move[i][a][j] = 1: i --a--> j  (0='a', 1='b', ...) */
int isFinal[20];

/* new move of q on symbol a:   q =e=> p --a--> r =e=> s */
void newMove(int q, int a) {
    int p, r, s;
    int result[20] = {0};

    for (p = 0; p < n; p++)
        if (closure[q][p])                  /* e moves from q to p */
            for (r = 0; r < n; r++)
                if (move[p][a][r])          /* read a, p to r */
                    for (s = 0; s < n; s++)
                        if (closure[r][s])  /* e moves from r to s */
                            result[s] = 1;

    printf("d'(q%d,%c) = { ", q, 'a' + a);
    for (s = 0; s < n; s++)
        if (result[s])
            printf("q%d ", s);
    printf("}\n");
}

int main() {
    int t, f, from, to, x, i, j, k, a;
    char sym;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols (a, b, ...): ");
    scanf("%d", &m);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to), e for epsilon:\n");
    for (i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &sym, &to);
        if (sym == 'e')
            closure[from][to] = 1;          /* e move goes in closure */
        else
            move[from][sym - 'a'][to] = 1;  /* real move goes in move */
    }

    printf("Enter number of final states: ");
    scanf("%d", &f);
    printf("Enter final states: ");
    for (i = 0; i < f; i++) {
        scanf("%d", &x);
        isFinal[x] = 1;
    }

    /* 1. e-closure (same as ec.c) */
    for (i = 0; i < n; i++)
        closure[i][i] = 1;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (closure[i][k] && closure[k][j])
                    closure[i][j] = 1;

    /* 2. new moves */
    for (i = 0; i < n; i++)
        for (a = 0; a < m; a++)
            newMove(i, a);

    /* 3. final states */
    printf("Final states: ");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (closure[i][j] && isFinal[j]) {
                printf("q%d ", i);
                break;
            }
    printf("\n");
    return 0;
}