%{
#include <stdio.h>

extern int yylex();
void yyerror(const char* s);
%}

%token NUM ID
%token LPAREN RPAREN SEMICOL
%token FOR WHILE DO
%token REL PLUS MINUS MUL DIV EQ

%%
s : FOR LPAREN assign SEMICOL cond SEMICOL assign RPAREN s { printf("FOR "); }
  | WHILE LPAREN cond RPAREN s { printf("WHILE "); }
  | DO s WHILE LPAREN cond RPAREN SEMICOL { printf("DO-WHILE "); }
  | assign SEMICOL { printf("= "); }
  ;

assign : id EQ e { printf("= "); }
       ;

cond : val REL val { printf("REL "); }
     ;

e : e PLUS t { printf("+ "); }
  | e MINUS t { printf("- "); }
  | t
  ;

t : t MUL f { printf("* "); }
  | t DIV f { printf("/ "); }
  | f
  ;

f : LPAREN e RPAREN
  | val
  ;

val : id
    | NUM { printf("NUM "); }
    ;

id : ID { printf("ID "); }
   ;
%%

int main() {
    if (yyparse()) {
        printf("\nInvalid syntax\n");
    } else {
        printf("\nValid syntax\n");
    }
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}
