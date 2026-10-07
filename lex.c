#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {"int", "float", "char", "if", "else", "while", "for", "return"};

int isKeyword(char *word) {
    int i;
    for (i = 0; i < 8; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

int main() {
    char fname[50], word[50];
    int ch, i;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch))                     /* 1. skip spaces */
            continue;

        if (isalpha(ch) || ch == '_') {      /* 2. keyword / identifier */
            i = 0;
            while (isalnum(ch) || ch == '_') {
                word[i++] = ch;
                ch = fgetc(fp);
            }
            word[i] = '\0';
            ungetc(ch, fp);
            if (isKeyword(word))
                printf("Keyword\t\t%s\n", word);
            else
                printf("Identifier\t%s\n", word);
        }
        else if (isdigit(ch)) {              /* 3. number */
            i = 0;
            while (isdigit(ch)) {
                word[i++] = ch;
                ch = fgetc(fp);
            }
            word[i] = '\0';
            ungetc(ch, fp);
            printf("Number\t\t%s\n", word);
        }
        else                                 /* 4. symbol */
            printf("Symbol\t\t%c\n", ch);
    }

    fclose(fp);
    return 0;
}