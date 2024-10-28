%{
#include <stdio.h>

int reg_cnt = 3;
int i = 0;
char reg_alloc[3] = {0, 0, 0};

extern int yylex();
void yyerror(const char* s);
int alloc_reg(char id);
%}

%union {
    int reg_num;
    char id;
}

%token <id> ID
%token PLUS MINUS MUL DIV EQ
%token ENDL

%type <reg_num> expr

%%
p: stt prog;

prog: stt ENDL prog | epsilon;

stt: ID EQ expr {
       reg_alloc[$3] = $1;
       printf("MOV %c, R%d\n", $1, $3);
   }
   ;

expr: ID PLUS ID {
        $$ = alloc_reg($1);
        printf("ADD R%d, R%d\n", $$, alloc_reg($3));
    }
    | ID MINUS ID {
        $$ = alloc_reg($1);
        printf("SUB R%d, R%d\n", $$, alloc_reg($3));
    }
    | ID MUL ID {
        $$ = alloc_reg($1);
        printf("MUL R%d, R%d\n", $$, alloc_reg($3));
    }
    | ID DIV ID {
        $$ = alloc_reg($1);
        printf("DIV R%d, R%d\n", $$, alloc_reg($3));
    }
    ;

epsilon: ;
%%

int alloc_reg(char id) {
    for (i = 0; i < 3; i++)
        if (reg_alloc[i] == id)
            return i;
    reg_cnt = (reg_cnt + 1) % 3;
    reg_alloc[reg_cnt] = id;
    printf("MOV R%d, %c\n", reg_cnt, id);
    return reg_cnt;
}

int main() {
    return yyparse();
}

void yyerror(const char* s) {
    fprintf(stderr, "Compiler error: %s\n", s);
}
