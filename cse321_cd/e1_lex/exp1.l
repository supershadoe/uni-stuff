%{
#include <stdio.h>
#include <sys/stat.h>

#define PRINT_TYPE(type) printf("%s is a %s\n", yytext, type)
#define ADD_TO_FILE(fptr) fprintf(fptr, "%s\n", yytext)

FILE *prep, *keyw, *opr, *iden, *lit, *comm, *punc;
%}

keyword int|char|float|struct|union|return|static|main
identifier [a-zA-Z_][a-zA-Z0-9_]*
operator \+|\-|\*|\/|%|==|=|\+\+|\-\-|\!|&&|\|\||\&|\||\^|~

%x mlc

%%

#.+ {
    ADD_TO_FILE(prep);
    PRINT_TYPE("preprocessor directive");
}

{keyword} {
    ADD_TO_FILE(keyw);
    PRINT_TYPE("keyword");
}

{operator} {
    ADD_TO_FILE(opr);
    PRINT_TYPE("operator");
}

{identifier}\( {
    PRINT_TYPE("function");
    yytext[yyleng - 1] = '\0';
    ADD_TO_FILE(iden);
}

{identifier} {
    ADD_TO_FILE(iden);
    PRINT_TYPE("identifier");
}

\) {
    ADD_TO_FILE(punc);
    PRINT_TYPE("end of arguments/expr");
}

\{ {
    ADD_TO_FILE(punc);
    PRINT_TYPE("start of a block");
}

\} {
    ADD_TO_FILE(punc);
    PRINT_TYPE("end of a block");
}

\".+\" {
    ADD_TO_FILE(lit);
    PRINT_TYPE("string");
}

[0-9]+ {
    ADD_TO_FILE(lit);
    PRINT_TYPE("integer");
}

[0-9]+\.[0-9]+ {
    ADD_TO_FILE(lit);
    PRINT_TYPE("float");
}

\'.\' {
    ADD_TO_FILE(lit);
    PRINT_TYPE("char");
}

\/\/.* {
    ADD_TO_FILE(comm);
    PRINT_TYPE("comment");
}

\/\* {
    ADD_TO_FILE(comm);
    PRINT_TYPE("start of multi line comment");
    BEGIN(mlc);
}

<mlc>\*\/ {
    ADD_TO_FILE(comm);
    PRINT_TYPE("end of multi line comment");
    BEGIN(INITIAL);
}

<mlc>. {
    fprintf(comm, "%s", yytext);
    ECHO;
}

; {
    ADD_TO_FILE(punc);
    PRINT_TYPE("line terminator");
}

[ \t\r\n]+ {}

. PRINT_TYPE("unmatched token");

%%

int main() {
    struct stat st;
    if (stat("gen", &st) == -1) {
        mkdir("gen", 0755);
    }
    prep = fopen("gen/prep", "w");
    keyw = fopen("gen/keyw", "w");
    opr = fopen("gen/opr", "w");
    iden = fopen("gen/iden", "w");
    lit = fopen("gen/lit", "w");
    comm = fopen("gen/comm", "w");
    punc = fopen("gen/punc", "w");
    yylex();
    return 0;
}

int yywrap() {
    fclose(prep);
    fclose(keyw);
    fclose(opr);
    fclose(iden);
    fclose(lit);
    fclose(comm);
    fclose(punc);
    return 1;
}
