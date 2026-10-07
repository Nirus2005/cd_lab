#include <stdio.h>

int n, m;
int next[20][10];     /* next[i][a] = state reached from i on symbol a */
int isFinal[20];
int diff[20][20];     /* diff[i][j] = 1: states i and j are different */

/* group name of x = smallest state that is NOT different from x */
int group(int x) {
    int j = 0;
    while (diff[x][j])
        j++;
    return j;
}

int main() {
    int f, x, y, i, j, a, changed;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols (a, b, ...): ");
    scanf("%d", &m);

    printf("Enter transition table (next state for each symbol), (-1 if no transision is present for that symbol):\n");
    for (i = 0; i < n; i++) {
        printf("q%d: ", i);
        for (a = 0; a < m; a++)
            scanf("%d", &next[i][a]);
    }

    printf("Enter number of final states: ");
    scanf("%d", &f);
    printf("Enter final states: ");
    for (i = 0; i < f; i++) {
        scanf("%d", &x);
        isFinal[x] = 1;
    }

        /* missing move (-1) goes to a dead state numbered n */
    dead = 0;
    for (i = 0; i < n; i++)
        for (a = 0; a < m; a++)
            if (next[i][a] == -1) {
                next[i][a] = n;
                dead = 1;
            }
    if (dead) {
        for (a = 0; a < m; a++)
            next[n][a] = n;      /* dead state loops to itself */
        n++;
    }

    /* 1. final vs non-final are different */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (isFinal[i] != isFinal[j])
                diff[i][j] = 1;

    /* 2. if a pair goes to a different pair, mark it. Repeat until no change */
    changed = 1;
    while (changed) {
        changed = 0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (a = 0; a < m; a++) {
                    x = next[i][a];
                    y = next[j][a];
                    if (diff[i][j] == 0 && diff[x][y] == 1) {
                        diff[i][j] = 1;
                        changed = 1;
                    }
                }
    }

    /* 3-4. print each group once, with moves pointing to group names */
    for (i = 0; i < n; i++) {
        if (group(i) == i) {              /* i is the smallest in its group */
            printf("q%d = { ", i);
            for (j = 0; j < n; j++)
                if (diff[i][j] == 0)
                    printf("q%d ", j);
            printf("}");
            for (a = 0; a < m; a++)
                printf("  %c -> q%d", 'a' + a, group(next[i][a]));
            if (isFinal[i])
                printf("  (final)");
            printf("\n");
        }
    }
    return 0;
}