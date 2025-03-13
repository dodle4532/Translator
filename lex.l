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
"u32" {yylval.str = strdup(yytext); return U32;}
"f32" {yylval.str = strdup(yytext); return F32;}
"u64" {yylval.str = strdup(yytext); return U64;}
"str" {yylval.str = strdup(yytext); return STR;}
"bool" {yylval.str = strdup(yytext); return BOOL;}
"true" {yylval.str = strdup(yytext); return TRUE;}
"false" {yylval.str = strdup(yytext); return TRUE;}
"fn"  {return FN;}
"int"  {return INT;}
"if"  {return IF;}
"else"  {return ELSE;}
"for"  {return FOR;}
"while"  {return WHILE;}
"return"  {return RETURN;}
"in"  {return IN;}
"=="  {yylval.str = strdup("=="); return EQUALS;}
"!="  {yylval.str = strdup("!="); return NOT_EQUALS;}
"<"  {yylval.str = strdup("<"); return LESS;}
"<="  {yylval.str = strdup("<="); return EQ_LESS;}
">="  {yylval.str = strdup(">="); return EQ_MORE;}
">"  {yylval.str = strdup(">"); return MORE;}
".."  {return TWO_POINTS;}
"\""  {return QUOTE;}
[a-zA-Z][a-zA-Z0-9]* {yylval.str = strdup(yytext); return WORD;}
":"      {return ':';}
"+"      {return '+';}
"-"      {return '-';}
"*"      {return '*';}
"/"      {return '/';}
";"      {return ';';}
","      {return ',';}
"="      {return '=';}
"("      {return '(';}
")"      {return ')';}
"{"      {return '{';}
"}"      {return '}';}

\"([^\"\n])*\" { const char* str_start = yytext + 1;
                 int len = strlen(yytext) - 2;
                 char* new_str = (char*)malloc(len + 1); // +1 для завершающего нуля
                 strncpy(new_str, str_start, len);
                 new_str[len] = '\0';
                 yylval.str = new_str;
                 return STRING;}

%%
