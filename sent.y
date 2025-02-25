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
    int integer;
    struct member_type* memb;
    struct value_type* _val;
}

%token <integer> NUM
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


%type <memb> command declaration initialization functionCall function if_expression
%type <integer> init assignment
%type <str> type
%type <_val> value val

%% /* The grammar follows. */

input:
  %empty
| input command
;



command:
  declaration {push_back(ast->declarations, $1);}
| initialization {push_back(ast->initializations, $1);}
| functionCall {push_back(ast->functionCalls, $1);}
| function {push_back(ast->functions, $1);}
| if_expression {push_back(ast->if_expressions, $1);}
;

declaration:
  LET WORD ':' type init ';' { int* a = malloc(sizeof(int));
                               *a = $5;
                               $$ = createMember(createValue(INTEGER_TYPE, a), $2);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = NULL;}

initialization:
  WORD assignment ';' { int* a = malloc(sizeof(int));
                        *a = $2;
                        $$ = createMember(createValue(INTEGER_TYPE, a), $1);}
;

assignment:
  '=' NUM {$$ = $2;}
;

type:
  U32
;

functionCall:
  WORD '(' value ')' ';'
;

value:
  val
| val ',' value
;

parametrs:
  par
| par ',' parametrs
;

par:
  INT WORD
| %empty
;

val:
  STRING
| NUM
| WORD
;

function:
  FN WORD '(' parametrs ')' brackets_functionImplementation
;

functionImplementation:
  funcImpl
| funcImpl functionImplementation
;

funcImpl:
  functionCall
| initialization
| declaration
;

brackets_functionImplementation:
  '{' functionImplementation '}'
;

if_expression:
  IF expression brackets_functionImplementation else_expression
;

else_expression:
  ELSE brackets_functionImplementation
| %empty
;

expression:
  val cmp val
;

cmp:
  EQUALS
| NOT_EQUALS
;

%%

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}