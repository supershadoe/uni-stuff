LEX := flex
YACC := yacc
CC := gcc

.PHONY: all test clean

all: codegen

test: all
	./codegen < inp.txt

codegen: lex.yy.c y.tab.c
	$(CC) -o codegen lex.yy.c y.tab.c

lex.yy.c: 12.l y.tab.h
	$(LEX) 12.l

y.tab.c y.tab.h: 12.y
	$(YACC) -d 12.y

clean:
	rm codegen lex.yy.c *.tab.*
