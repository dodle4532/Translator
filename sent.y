%{
  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h> // Для NULL
  #include <string.h>
  #include "lex.h"
  #include "ast.h"
  #include "astHelper.h"
  int yylex (void);
  void yyerror (char *s);
  extern struct ast* ast;
  int num = 1;
  struct command_type* forCommand = NULL;
  enum VALUE_TYPE getValueType(char* val) {
      if (!strcmp(val, "bool")) {
          return BOOLEAN_TYPE;
      }
      if (!strcmp(val, "u32") || !strcmp(val, "u64")) {
          return INTEGER_TYPE;
      }
      if (!strcmp(val, "f32")) {
          return FLOAT_TYPE;
      }
      if (!strcmp(val, "str")) {
          return STRING_TYPE;
      }
      return NULL_TYPE;
  }
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
    struct if_cond_type* if_cond;
    struct if_expr_type* if_expr;
}

%token <integer> NUM
%token <str> WORD
%token <str> STRING
%token LET
%token <str> U32
%token <str> U64
%token <str> F32
%token <str> STR
%token <str> BOOL
%token <integer> TRUE
%token <integer> FALSE
%token FN
%token INT
%token IF
%token ELSE
%token FOR
%token WHILE
%token <str> EQUALS
%token <str> NOT_EQUALS
%token QUOTE
%token IN
%token TWO_POINTS
%token RETURN
%token <str> LESS
%token <str> MORE
%token <str> EQ_LESS
%token <str> EQ_MORE

// Определяем типы для нетерминалов


%type <com> command declaration initialization if_expression functionCall function while_expression for_expression
%type <str> type cmp
%type <_val> val expr second assignment init ret returnVal
%type <memb> par
%type <valVec> value  
%type <membVec> parametrs
%type <ast_type> functionImplementation brackets_functionImplementation funcImpl
%type <if_cond> expression
%type <if_expr> else_expression

%% /* The grammar follows. */

input:
  %empty
| input command {}
;

command:
  declaration {push_back_com(ast->declarations, $1);}
| initialization {push_back_com(ast->initializations, $1);}
| functionCall {push_back_com(ast->functionCalls, $1);}
| function {push_back_com(ast->functions, $1);}
| if_expression {push_back_com(ast->if_expressions, $1);}
| while_expression {push_back_com(ast->cycles, $1);}
| for_expression {push_back_com(ast->cycles, $1); push_back_com(ast->declarations, forCommand);}
;

declaration:
  LET WORD ':' type init ';' { 
                               struct member_type* mem = createMember($5, $2);
                               $$ = createCommand(num++, MEMBER_COM_TYPE, mem); free($4);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = createValue(NULL_TYPE, NULL);}

initialization:
  WORD assignment ';' { struct member_type* mem = createMember($2, $1);
                        $$ = createCommand(num++, INIT_COM_TYPE, mem);}
;

assignment:
  '=' expr {$$ = $2;}
;

type:
  U32  {$$ = $1;}
| U64  {$$ = $1;}
| F32  {$$ = $1;}
| STR  {$$ = $1;}
| BOOL {$$ = $1;}
;

functionCall:
  WORD '(' value ')' ';' { struct func_call_type* f = createFuncCall($1, $3);
                           $$ = createCommand(num++, FUNC_CALL_TYPE, f);}
;

value:
  %empty        {$$ = createValueVec();}
| val           {$$ = createValueVec();
                 push_back_val($$, $1);}
| val ',' value {$$ = createValueVec();
                 push_back_val($$, $1);
                 for(int i = 0; i < $3->size; ++i) {
                  push_back_val($$, $3->values[i]);
                 }}
;

parametrs:
  par               {$$ = createMemberVec();
                     if ($1->value->type != NULL_TYPE) push_back_mem($$, $1);}
| par ',' parametrs {$$ = createMemberVec();
                     push_back_mem($$, $1);
                     for(int i = 0; i < $3->size; ++i) {
                      push_back_mem($$, $3->members[i]);
                     }}
;

par:
  type WORD {$$ = createMember(createValue(getValueType($1), NULL), $2);}
| %empty   {$$ = createMember(createValue(NULL_TYPE, NULL), NULL);}
;

val:
  STRING { char* str = calloc(64, sizeof(char));
           strcpy(str, $1);
           $$ = createValue(STRING_TYPE, str); free($1);} 
| NUM    { int* a = malloc(sizeof(int));
           *a = $1;
           $$ = createValue(INTEGER_TYPE, a);}
| WORD   { char* str = calloc(64, sizeof(char));
           strcpy(str, $1);
           $$ = createValue(OBJECT_TYPE, str); free($1);}
| TRUE   { int* a = malloc(sizeof(int));
           *a = $1;
           $$ = createValue(BOOLEAN_TYPE, a);}
| FALSE   { int* a = malloc(sizeof(int));
           *a = $1;
           $$ = createValue(BOOLEAN_TYPE, a);}
;

function:
  FN WORD '(' parametrs ')' '{' functionImplementation ret '}' { struct func_impl_type* res = createFuncImpl($2, $4, $7, $8);
                                                                          $$ = createCommand(num++, FUNC_IMPL_TYPE, (void*)res);}
;

functionImplementation:
  funcImpl                        { $$ = $1;}
| funcImpl functionImplementation { $$ = mergeAst($1, $2);}
;

ret:
  RETURN returnVal ';' {$$ = $2;}
| %empty {$$ = createValue(NULL_TYPE, NULL);}
;

returnVal:
  expr {$$ = $1;}
| %empty {$$ = createValue(NULL_TYPE, NULL);}
;

funcImpl:
  functionCall {$$ = createAst(); push_back_com($$->functionCalls, $1);}
| initialization {$$ = createAst(); push_back_com($$->initializations, $1);}
| declaration {$$ = createAst(); push_back_com($$->declarations, $1);}
| if_expression {$$ = createAst(); push_back_com($$->if_expressions, $1);}
| while_expression {$$ = createAst(); push_back_com($$->cycles, $1);}
| for_expression {$$ = createAst(); push_back_com($$->cycles, $1); push_back_com($$->declarations, forCommand);}
;

brackets_functionImplementation:
  '{' functionImplementation '}' {$$ = $2;}
;

if_expression:
  IF expression brackets_functionImplementation else_expression {
                                                                  struct if_expr_type* res = createIfExpr($2, $3, $4);
                                                                  $$ = createCommand(num++, IF_COM_TYPE, (void*)res);
                                                                  }
;

else_expression:
  ELSE brackets_functionImplementation {$$ = createIfExpr(NULL, $2, NULL);}
| %empty {$$ = NULL;}
;

expression:
  val cmp val {$$ = createIfCond($2, $1, $3);}
;

cmp:
  EQUALS {$$ = $1;}
| NOT_EQUALS {$$ = $1;}
| LESS {$$ = $1;}
| MORE {$$ = $1;}
| EQ_LESS {$$ = $1;}
| EQ_MORE {$$ = $1;}
;

while_expression:
  WHILE expression brackets_functionImplementation {  struct cycle_type* res = createCycle($2, $3);
                                                      $$ = createCommand(num++, CYCLE_COM_TYPE, (void*)res);num++;}
;

for_expression:
  FOR WORD IN NUM TWO_POINTS NUM brackets_functionImplementation {int* a = calloc(16, sizeof(int));*a = $4;
                                                                  int* b = calloc(16, sizeof(int));*b = $6;
                                                                  struct cycle_type* res = createCycle(createIfCond(strdup("<="),
                                                                  createValue(OBJECT_TYPE,$2),createValue(INTEGER_TYPE,b)), $7);
                                                                  forCommand = createCommand(num++, MEMBER_COM_TYPE, (struct command_type*)createMember(createValue(INTEGER_TYPE,a),$2));
                                                                  char* str = calloc(16, sizeof(char));
                                                                  strcat(str, $2); strcat(str, "+1");
                                                                  push_back_com(res->body->initializations, createCommand(num++, INIT_COM_TYPE, (struct command_type*)createMember(createValue(OBJECT_TYPE, str), $2)));
                                                                  $$ = createCommand(num++, CYCLE_COM_TYPE, (void*)res);}
;

expr:
  second '+' expr {$$ = getOp($1, $3, '+'); if ($$ == NULL) {YYABORT;}}
| second '-' expr {$$ = getOp($1, $3, '-'); if ($$ == NULL) {YYABORT;}}
| second          {$$ = $1;}
;

second:
  val '*' second {$$ = getOp($1, $3, '*'); if ($$ == NULL) {;YYABORT;}}
| val '/' second {$$ = getOp($1, $3, '/'); if ($$ == NULL) {YYABORT;}}
| val            {$$ = $1;}
;

%%

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}