%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z_0-9]* return ID;
[0-9]+\.[0-9]+ return FLOAT;
[0-9]+ return INT;
[ \t\r\n] {}
. return yytext[0];
%%

int yywrap() { return 1; } 
