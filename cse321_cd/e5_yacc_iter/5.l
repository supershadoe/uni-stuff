%{
#include "y.tab.h"
%}

%%
for return FOR;
while return WHILE;
do return DO;
"(" return LPAREN;
")" return RPAREN;
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"=" return EQ;
";" return SEMICOL;
0|[1-9][0-9]* return NUM;
[a-zA-Z_][a-zA-Z_0-9]* return ID;
\<|\>|\>\=|\<\=|\=\=|\!\= return REL;
[ \t\r\n] {}
. return yytext[0];
%%

int yywrap() { return 1; } 
