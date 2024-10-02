%{
#include "y.tab.h"
%}

%%
if return IF;
else return ELSE;

for return FOR;
while return WHILE;
do return DO;

"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"%" return MOD;
"=" return EQ;

"(" return LPAREN;
")" return RPAREN;
"," return COMMA;
";" return SEMICOL;

\".*\" return STR;
0|[1-9][0-9]* return NUM;
[a-zA-Z_][a-zA-Z_0-9]* return ID;

\<|\>|\>\=|\<\=|\=\=|\!\= return REL;

[ \t\r\n] {}

. return yytext[0];
%%

int yywrap() { return 1; } 
