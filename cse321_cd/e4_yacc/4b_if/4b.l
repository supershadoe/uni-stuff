%{
#include "y.tab.h"
%}

%%
if { printf("IF"); return IF; } 
else { printf("ELSE"); return ELSE; }
[a-zA-Z_][a-zA-Z_0-9]* { printf("ID"); return ID; }
\<|\>|\>\=|\<\=|\=\=|\!\= { printf("REL"); return REL;}
[ \t\r\n] ECHO;
. { ECHO; return yytext[0]; }
%%

int yywrap() { return 1; } 
