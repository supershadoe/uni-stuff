%{
#include <stdio.h>

extern int yylex();
void yyerror(const char* s);
%}

%token INT
%token FLOAT
%token ID

%%
E : E '+' T { printf("+ "); }
  | T
  ;

T : T '*' F { printf("* "); }
  | F
  ;

F : '(' E ')'
  | ID { printf("ID "); }
  | INT { printf("INT "); }
  | FLOAT { printf("FLOAT "); }
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
