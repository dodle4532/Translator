all: build

build: sent.tab.h sent.c main.c
	flex --header-file="lex.h" lex.l
	gcc main.c sent.c lex.yy.c ast.c

sent.tab.h sent.c: sent.y
	bison --defines=sent.tab.h --output=sent.c sent.y
