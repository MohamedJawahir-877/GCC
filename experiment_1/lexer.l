%{
#include <stdio.h>
%}

%%
[0-9]+        { printf("NUMBER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
[ \t\n]+      ;   /* ignore whitespace */
.             { printf("SYMBOL: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}
