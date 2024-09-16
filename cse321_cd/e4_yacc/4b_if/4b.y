%{
#include <stdio.h>

extern int yylex();
void yyerror(const char* s);
%}

%token IF
%token ELSE
%token ID
%token REL

%%
S : IF '(' C ')' S { printf("\t==> simple if statement\n"); }
  | IF '(' C ')' S ELSE S { printf("\t==> if-else statement\n"); }
  | ID '=' E ';' { printf("\t==> assignment\n"); }
  ;

C : ID REL ID { printf("\t==> comparison\n"); }
  ;

E : E '+' T { printf("\t==> addition\n"); }
  | T
  ;

T : T '*' F { printf("\t==> multiplication\n"); }
  | F
  ;

F : '(' E ')' { printf("\t==> brackets\n"); }
  | ID
  ;
%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}
