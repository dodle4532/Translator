%option noyywrap

%{
#include <stdio.h>


#include "sent.tab.h"

%}

%%

[ \t] ; // ignore all whitespace
[ \n] ;
[0-9]+      {yylval.integer = atoi(yytext); return NUM;}
"let" {return LET;}
"u32" {return U32;}
"fn"  {return FN;}
"int"  {return INT;}
"if"  {return IF;}
"else"  {return ELSE;}
"for"  {return FOR;}
"while"  {return WHILE;}
"=="  {return EQUALS;}
"!="  {return NOT_EQUALS;}
"\""  {return QUOTE;}

[a-zA-Z][a-zA-Z0-9]* {yylval.str = strdup(yytext); return WORD;}
":"      {return ':';}
"+"      {return '+';}
"*"      {return '*';}
";"      {return ';';}
","      {return ',';}
"="      {return '=';}
"("      {return '(';}
")"      {return ')';}
"{"      {return '{';}
"}"      {return '}';}

\"([^\"\n])*\" {return STRING;}

%%
