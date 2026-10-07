%{
#include <stdio.h>
int yylex();
void yyerror(char *s) { printf("Invalid expression\n"); }
%}

%token NUM ID
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
line : expr '\n'       { printf("Valid expression\n"); YYACCEPT; }
     ;
expr : expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | '(' expr ')'
     | '-' expr %prec UMINUS
     | NUM
     | ID
     ;
%%

int main() { yyparse(); return 0; }