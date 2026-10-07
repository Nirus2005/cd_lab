%{
#include <stdio.h>
%}

%option caseless

%%
.*name.*    { puts("REJECT"); }
.+          { puts("ACCEPT"); }
\n          ;
%%
int main(void) {
    yylex();
    return 0;
}
int yywrap(void) {
    return 1;
}
