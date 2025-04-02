all: build

build: sent.tab.h sent.c lex.yy.c main.c
	gcc -g main.c sent.c lex.yy.c ast.c astHelper.c

sent.tab.h sent.c: sent.y
	bison --defines=sent.tab.h --output=sent.c sent.y

lex.yy.c: lex.l
	flex --header-file="lex.h" lex.l
