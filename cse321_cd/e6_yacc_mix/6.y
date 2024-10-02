%{
#include <stdio.h>

extern int yylex();
void yyerror(const char* s);
%}

%token STR NUM ID
%token LPAREN RPAREN COMMA SEMICOL
%token IF ELSE
%token FOR WHILE DO
%token REL PLUS MINUS MUL DIV MOD EQ

%%
s : IF LPAREN cond RPAREN s { printf("IF "); }
  | IF LPAREN cond RPAREN s ELSE s { printf("IF-ELSE "); }
  | FOR LPAREN assign SEMICOL cond SEMICOL assign RPAREN s { printf("FOR "); }
  | WHILE LPAREN cond RPAREN s { printf("WHILE "); }
  | DO s WHILE LPAREN cond RPAREN SEMICOL { printf("DO-WHILE "); }
  | id LPAREN arg RPAREN SEMICOL { printf("CALL "); }
  | assign SEMICOL
  ;

arg :
    | val COMMA arg
    | val
    ;

assign : id EQ e { printf("= "); }
       ;

cond : e REL e { printf("REL "); }
     ;

e : e PLUS t { printf("+ "); }
  | e MINUS t { printf("- "); }
  | t
  ;

t : t MUL f { printf("* "); }
  | t DIV f { printf("/ "); }
  | t MOD f { printf("%% "); }
  | f
  ;

f : LPAREN e RPAREN
  | val
  ;

val : id
    | STR { printf("STR "); }
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
