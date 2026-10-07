#include <stdio.h>

int n, m, count;
int move[20][10][20];   /* move[i][a][j] = 1: NFA has i --a--> j */
int isFinal[20];
int dfa[50][20];        /* dfa[d][i] = 1: NFA state i is inside DFA state d */

void printSet(int set[]) {
    int i;
    printf("{ ");
    for (i = 0; i < n; i++)
        if (set[i])
            printf("q%d ", i);
    printf("}");
}

/* return the DFA state number of this set, or -1 if it is new */
int find(int set[]) {
    int d, i, same;
    for (d = 0; d < count; d++) {
        same = 1;
        for (i = 0; i < n; i++)
            if (dfa[d][i] != set[i])
                same = 0;
        if (same)
            return d;
    }
    return -1;
}

int main() {
    int t, f, from, to, x, i, j, d, a;
    int target[20];
    char sym;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols (a, b, ...): ");
    scanf("%d", &m);
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");
    for (i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &sym, &to);
        move[from][sym - 'a'][to] = 1;
    }

    printf("Enter number of final states: ");
    scanf("%d", &f);
    printf("Enter final states: ");
    for (i = 0; i < f; i++) {
        scanf("%d", &x);
        isFinal[x] = 1;
    }

    /* 1. start state is { q0 } */
    dfa[0][0] = 1;
    count = 1;

    /* 2-4. process DFA states one by one; new ones join the end of the list */
    for (d = 0; d < count; d++) {
        for (a = 0; a < m; a++) {
            /* 2. target = every state reached on a from any member of dfa[d] */
            for (j = 0; j < n; j++)
                target[j] = 0;
            for (i = 0; i < n; i++)
                if (dfa[d][i])
                    for (j = 0; j < n; j++)
                        if (move[i][a][j])
                            target[j] = 1;

            /* 3. new set becomes a new DFA state (empty set = dead state) */
            if (find(target) == -1) {
                for (j = 0; j < n; j++)
                    dfa[count][j] = target[j];
                count++;
            }

            printSet(dfa[d]);
            printf(" --%c--> ", 'a' + a);
            printSet(target);
            printf("\n");
        }
    }

    /* 5. final if the set contains an NFA final state */
    printf("Final states: ");
    for (d = 0; d < count; d++)
        for (i = 0; i < n; i++)
            if (dfa[d][i] && isFinal[i]) {
                printSet(dfa[d]);
                printf(" ");
                break;
            }
    printf("\n");
    return 0;
}