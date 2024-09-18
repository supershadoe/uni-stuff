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
S : IF '(' C ')' S { printf("IF "); }
  | IF '(' C ')' S ELSE S { printf("IF-ELSE "); }
  | I '=' E ';' { printf("= "); }
  ;

C : I REL I { printf("REL "); }
  ;

E : E '+' T { printf("+ "); }
  | T
  ;

T : T '*' F { printf("* "); }
  | F
  ;

F : '(' E ')'
  | I
  ;

I : ID { printf("ID "); }
  ;
%%

int main() {
    yyparse();
    printf("\n");
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}
