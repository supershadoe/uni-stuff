%{
#include <stdio.h>
#include "type.h"

extern int yylex();
void yyerror(const char* s);

int temp = -1;
%}

%union {
    TEMPNO temp_no;
    int num;
    char *id;
}

%token <num> NUM
%token <id> ID
%token LPAREN RPAREN
%token PLUS MINUS MUL DIV MOD EQ

%type <temp_no> e t f

%%
e : e PLUS t {
      $$ = ++temp;
      printf("t%d = t%d + t%d\n", temp, $1, $3);
  }
  | e MINUS t {
      $$ = ++temp;
      printf("t%d = t%d - t%d\n", temp, $1, $3);
  }
  | t
  ;

t : t MUL f {
      $$ = ++temp;
      printf("t%d = t%d * t%d\n", temp, $1, $3);
  }
  | t DIV f {
      $$ = ++temp;
      printf("t%d = t%d / t%d\n", temp, $1, $3);
  }
  | t MOD f {
      $$ = ++temp;
      printf("t%d = t%d %% t%d\n", temp, $1, $3);
  }
  | f
  ;

f : LPAREN e RPAREN { $$ = $2; }
  | ID {
      $$ = ++temp;
      printf("t%d = %s\n", temp, $1);
  }
  | NUM {
      $$ = ++temp;
      printf("t%d = %d\n", temp, $1);
  }
  ;
%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}