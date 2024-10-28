%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = yytext[0]; return ID; }

"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"=" return EQ;

"\n" return ENDL;
[ \t\r] {}

. return yytext[0];
%%

int yywrap() { return 1; }
