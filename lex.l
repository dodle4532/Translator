%option noyywrap

%{
#include <stdio.h>


#include "sent.tab.h"

%}

%%

[ \t] ; // ignore all whitespace
[ \n] ;
[0-9]+      {yylval.integer = atoi(yytext); return NUM;}
[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?      { yylval.fl = atof(yytext); return FLOAT; }
"let" {return LET;}
"u32" {yylval.str = strdup(yytext); return U32;}
"f32" {yylval.str = strdup(yytext); return F32;}
"u64" {yylval.str = strdup(yytext); return U64;}
"str" {yylval.str = strdup(yytext); return STR;}
"bool" {yylval.str = strdup(yytext); return BOOL;}
"true" {yylval.integer = 1; return TRUE;}
"false" {yylval.integer = 0; return FALSE;}
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
"->"  {return ARROW;}
"\""  {return QUOTE;}
[a-zA-Z][a-zA-Z0-9!]* {yylval.str = strdup(yytext); return WORD;}
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

\"([^\"\n])*\" {
    const char* str_start = yytext + 1;
    int len = strlen(yytext) - 2;
    char* new_str = (char*)malloc(len + 1);
    int j = 0; // Индекс для записи в new_str
    for (int i = 0; i < len; ++i) {
        if (str_start[i] == '\\') {
            // Обработка escape-последовательности
            switch (str_start[i + 1]) {
                case 'n':
                    new_str[j++] = '\n';
                    i++; // Пропускаем 'n'
                    break;
                case 't':
                    new_str[j++] = '\t';
                    i++; // Пропускаем 't'
                    break;
                case '\\':
                    new_str[j++] = '\\';
                    i++; // Пропускаем второй '\'
                    break;
                case '"':
                    new_str[j++] = '"';
                    i++; // Пропускаем '"'
                    break;
                default:
                    // Неизвестная escape-последовательность, просто копируем '\' и следующий символ
                    new_str[j++] = str_start[i];
                    break;

            }
        } else {
            new_str[j++] = str_start[i];
        }
    }
    new_str[j] = '\0'; // Null-terminate the string

    // Теперь, если j < len, значит были escape-последовательности, и можно уменьшить размер выделенной памяти
    if (j < len) {
      new_str = (char*)realloc(new_str, j + 1); //realloc
      if (!new_str) {
        fprintf(stderr, "Memory reallocation failed!\n");
        exit(1);
      }
    }

    yylval.str = new_str;
    return STRING;
}

%%
