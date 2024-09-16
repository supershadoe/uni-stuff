%{
#include <stdio.h>

extern int yylex();
void yyerror(const char* s);
%}

%token INT
%token FLOAT
%token ID

%%
E : E '+' T { printf("\t==> addition\n"); }
  | T
  ;

T : T '*' F { printf("\t==> multiplication\n"); }
  | F
  ;

F : '(' E ')' { printf("\t==> brackets\n"); }
  | ID
  | INT
  | FLOAT
  ;
%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}
