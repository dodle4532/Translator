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
  int num = 1;
%}
%union {
    char* str;
    int integer;
    struct member_type* memb;
    struct value_type* _val;
    struct value_vec* valVec;
    struct command_type* com;
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


%type <com> command declaration initialization function if_expression functionCall
%type <integer> init assignment
%type <str> type
%type <_val> val
%type <valVec> value
%type <func_call_type> func_call

%% /* The grammar follows. */

input:
  %empty
| input command {num++;}
;



command:
  declaration {push_back_com(ast->declarations, $1);}
| initialization {push_back_com(ast->initializations, $1);}
| functionCall {push_back_com(ast->functionCalls, $1);}
| function
| if_expression
;

declaration:
  LET WORD ':' type init ';' { int* a = malloc(sizeof(int));
                               *a = $5;
                               struct member_type* mem = createMember(createValue(INTEGER_TYPE, a), $2);
                               $$ = createCommand(num, mem);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = NULL;}

initialization:
  WORD assignment ';' { int* a = malloc(sizeof(int));
                        *a = $2;
                        struct member_type* mem = createMember(createValue(INTEGER_TYPE, a), $1);
                        $$ = createCommand(num, mem);}
;

assignment:
  '=' NUM {$$ = $2;}
;

type:
  U32
;

functionCall:
  WORD '(' value ')' ';' { struct func_call_type* f = createFuncCall($1, $3);
                           $$ = createCommand(num, f);}
;

value:
  val           {$$ = createValueVec();
                 push_back_val($$, $1);}
| val ',' value {$$ = createValueVec();
                 push_back_val($$, $1);
                 for(int i = 0; i < $3->size; ++i) {
                  push_back_val($$, $3->values[i]);
                 }}
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
  STRING { char* str = calloc(64, sizeof(char));
           strcpy(str, $1);
           $$ = createValue(STRING_TYPE, str);} 
| NUM    { int* a = malloc(sizeof(int));
           *a = $1;
           $$ = createValue(INTEGER_TYPE, a);}
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