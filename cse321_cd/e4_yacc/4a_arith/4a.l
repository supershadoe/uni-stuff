%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z_0-9]* { printf("ID"); return ID; }
[0-9]+\.[0-9]+ { printf("FLOAT"); return FLOAT; }
[0-9]+ { printf("INT"); return INT; }
[ \t\r\n] ECHO;
. { ECHO; return yytext[0]; }
%%

int yywrap() { return 1; } 
