%{
#include <stdlib.h>
#include "type.h"
#include "y.tab.h"
%}

%%
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"%" return MOD;
"=" return EQ;

"(" return LPAREN;
")" return RPAREN;

0|[1-9][0-9]* {
    yylval.num = atoi(yytext);
    return NUM;
}
[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.id = yytext;
    return ID;
}

[ \t\r\n] {}

. return yytext[0];
%%

int yywrap() { return 1; } 