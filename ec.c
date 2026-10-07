#include <stdio.h>

int reach[20][20];   /* reach[i][j] = 1 means state j is in e-closure of state i */

int main() {
    int n, t, from, to, i, j, k;
    char sym;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    /* 1. read transitions, keep only e moves */
    printf("Enter transitions (from symbol to):\n");
    for (i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &sym, &to);
        if (sym == 'e')
            reach[from][to] = 1;
    }

    /* 2. every state reaches itself */
    for (i = 0; i < n; i++)
        reach[i][i] = 1;

    /* 3. chain: i -> k and k -> j means i -> j */
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (reach[i][k] && reach[k][j])
                    reach[i][j] = 1;

    /* 4. print each row */
    for (i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        for (j = 0; j < n; j++)
            if (reach[i][j])
                printf("q%d ", j);
        printf("}\n");
    }
    return 0;
}