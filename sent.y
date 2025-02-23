%{
  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h> // Для NULL
  #include <string.h>
  #include "lex.h"
  #include "ast.h"
  int yylex (void);
  void yyerror (char *s);
  extern struct ast* ast;
%}
%union {
    char* str;
    struct member_type* memb;
}

%token NUM
%token <str> WORD
%token <str> STRING
%token LET
%token U32
%token FN
%token INT
%token IF
%token ELSE
%token FOR
%token WHILE
%token EQUALS
%token NOT_EQUALS
%token QUOTE

// Определяем типы для нетерминалов
%type <str> command declaration initialization functionCall function if_expression
%type <str> type init assignment value parametrs par brackets_functionImplementation
%type <str> functionImplementation funcImpl else_expression expression cmp val

%% /* The grammar follows. */

input:
  %empty
| input command
;



command:
  declaration {$$ = $1;}
| initialization {$$ = $1;}
| functionCall {$$ = $1;}
| function {$$ = $1;}
| if_expression {$$ = $1;}
;

declaration:
  LET WORD ':' type init ';' {$$ = NULL; free($2);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = NULL;}

initialization:
  WORD assignment ';' {$$ = NULL; free($1);}
;

assignment:
  '=' NUM {$$ = NULL;}
;

type:
  U32 {$$ = NULL;}
;

functionCall:
  WORD '(' value ')' ';' {$$ = NULL; free($1);}
;

value:
  val {$$ = $1;}
| val ',' value {$$ = NULL;}
;

parametrs:
  par {$$ = $1;}
| par ',' parametrs {$$ = NULL;}
;

par:
  INT WORD {$$ = NULL;}
| %empty {$$ = NULL;}
;

val:
  STRING {$$ = $1; free($1);}
| NUM {$$ = NULL;}
| WORD {$$ = NULL;}
;

function:
  FN WORD '(' parametrs ')' brackets_functionImplementation {$$ = NULL; free($2);}
;

functionImplementation:
  funcImpl {$$ = $1;}
| funcImpl functionImplementation {$$ = NULL;}
;

funcImpl:
  functionCall {$$ = $1;}
| initialization {$$ = $1;}
| declaration {$$ = $1;}
;

brackets_functionImplementation:
  '{' functionImplementation '}' {$$ = NULL;}
;

if_expression:
  IF expression brackets_functionImplementation else_expression {$$ = NULL;}
;

else_expression:
  ELSE brackets_functionImplementation {$$ = NULL;}
| %empty {$$ = NULL;}
;

expression:
  val cmp val {$$ = NULL;}
;

cmp:
  EQUALS {$$ = NULL;}
| NOT_EQUALS {$$ = NULL;}
;

%%

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}