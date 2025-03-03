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
    struct member_vec* membVec;
    struct command_type* com;
    struct ast* ast_type;
    struct func_impl_type* f_impl_type;
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


%type <com> command declaration initialization if_expression functionCall
%type <integer> init assignment
%type <str> type
%type <_val> val
%type <memb> par
%type <valVec> value
%type <membVec> parametrs
%type <ast_type> functionImplementation brackets_functionImplementation funcImpl
%type <f_impl_type> function

%% /* The grammar follows. */

input:
  %empty
| input command {num++;}
;



command:
  declaration {push_back_com(ast->declarations, $1);}
| initialization {push_back_com(ast->initializations, $1);}
| functionCall {push_back_com(ast->functionCalls, $1);}
| function {push_back_fImpl(ast->functions, $1);}
| if_expression {push_back_fImpl(ast->if_expressions, $1);}
;

declaration:
  LET WORD ':' type init ';' { int* a = malloc(sizeof(int));
                               *a = $5;
                               struct member_type* mem = createMember(createValue(INTEGER_TYPE, a), $2);
                               $$ = createCommand(num, mem);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = -1;}

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
  par               {$$ = createMemberVec();
                     push_back_mem($$, $1);}
| par ',' parametrs {$$ = createMemberVec();
                     push_back_mem($$, $1);
                     for(int i = 0; i < $3->size; ++i) {
                      push_back_mem($$, $3->members[i]);
                     }}
;

par:
  INT WORD {$$ = createMember(createValue(INTEGER_TYPE, NULL), $2);}
| %empty   {$$ = createMember(createValue(NULL_TYPE, NULL), NULL);}
;

val:
  STRING { char* str = calloc(64, sizeof(char));
           strcpy(str, $1);
           $$ = createValue(STRING_TYPE, str);} 
| NUM    { int* a = malloc(sizeof(int));
           *a = $1;
           $$ = createValue(INTEGER_TYPE, a);}
| WORD   { char* str = calloc(64, sizeof(char));
           strcpy(str, $1);
           $$ = createValue(OBJECT_TYPE, str);}
;

function:
  FN WORD '(' parametrs ')' brackets_functionImplementation { $$ = createFuncImpl($2, $4, $6); }
;

functionImplementation:
  funcImpl                        { $$ = createAst();
                                    mergeAst($$, $1);}
| funcImpl functionImplementation { $$ = createAst();
                                    mergeAst($$, $1); mergeAst($$, $2);}
;

funcImpl:
  functionCall {$$ = createAst(); push_back_com($$->functionCalls, $1);}
| initialization {$$ = createAst(); push_back_com($$->initializations, $1);}
| declaration {$$ = createAst(); push_back_com($$->declarations, $1);}
;

brackets_functionImplementation:
  '{' functionImplementation '}' {$$ = $2;}
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