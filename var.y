%{
#include <stdio.h>
int yylex(void);

void yyerror(const char *msg) {
    (void)msg;
    puts("Invalid variable");
}
%}

%token L D  

%%
variable : L rest '\n'    { puts("Valid variable"); YYACCEPT; } ;
rest : rest L | rest D | ;
%%

int main(void) {
    return yyparse();
}
