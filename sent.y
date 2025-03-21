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
  int getIntRes(int l, int r, const char* op) {
    if (!strcmp(op, "+")) {
      return l + r;
    }
    if (!strcmp(op, "-")) {
      return l - r;
    }
    if (!strcmp(op, "*")) {
      return l * r;
    }
    if (!strcmp(op, "/")) {
      return l / r;
    }
  }
  float getFloatRes(float l, float r, const char* op) {
    if (!strcmp(op, "+")) {
      return l + r;
    }
    if (!strcmp(op, "-")) {
      return l - r;
    }
    if (!strcmp(op, "*")) {
      return l * r;
    }
    if (!strcmp(op, "/")) {
      return l / r;
    }
  }
  struct value_type* getOp(struct value_type* left, struct value_type* right, const char* op) {
    struct value_type* val = calloc(1, sizeof(struct value_type));
    if (left->type == INTEGER_TYPE && right->type == INTEGER_TYPE) {
      val->type = INTEGER_TYPE;
      int* a = malloc(sizeof(int));
      *a = getIntRes(*(int*)left->data, *(int*)right->data, op);
      val->data = a;
      if (left->data != NULL) {
        free(left->data);
      }
      free(left);
      if (right->data != NULL) {
        free(right->data);
      }
      free(right);
      return val;
    }
    if (left->type == FLOAT_TYPE && right->type == FLOAT_TYPE) {
      val->type = FLOAT_TYPE;
      float* a = malloc(sizeof(float));
      *a = getFloatRes(*(float*)left->data, *(float*)right->data, op);
      val->data = a;
      if (left->data != NULL) {
        free(left->data);
      }
      free(left);
      if (right->data != NULL) {
        free(right->data);
      }
      free(right);
      return val;
    }
    if (strcmp(op, "+")) {
      free(val);
      return NULL;
    }
    if (left->type == BOOLEAN_TYPE || right->type == BOOLEAN_TYPE || left->type == NULL_TYPE || right->type == NULL_TYPE) {
      free(val); return NULL;
    }
    if (left->type == OBJECT_TYPE || right->type == OBJECT_TYPE) {
      char* l1;
      char* l2;
      if (left->type == INTEGER_TYPE) {
        l1 = calloc(32,sizeof(char));
        sprintf(l1, "%d", *(int*)left->data);
        free(left->data);
        left->data = NULL;
      }
      else {
        l1 = (char*)left->data;
      }
      if (right->type == INTEGER_TYPE) {
        l2 = calloc(32,sizeof(char));
        sprintf(l2, "%d", *(int*)right->data);
        free(right->data);
        right->data = NULL;
      }
      else {
        l2 = (char*)right->data;
      }
      val->type = OBJECT_TYPE;
      strcat(l1, "+"); strcat(l1, l2);
      val->data = l1;
      free(l2);
      return val;
    }
    if (left->type == STRING_TYPE && left->type == STRING_TYPE && op == "+") {
        strcat((char*) left->data, (char*)right->data);
        val->type = STRING_TYPE;
        val->data = strdup((char*)left->data);
        free(right->data);
        free(right);
        free(left->data);
        free(left);
        return val;
    }
    if (left->data != NULL) {
      free(left->data);
    }
    free(left);
    if (right->data != NULL) {
      free(right->data);
    }
    free(right);
    free(val);
    return NULL;
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
| input command {num++;}
;

command:
  declaration {push_back_com(ast->declarations, $1);}
| initialization {push_back_com(ast->initializations, $1);}
| functionCall {push_back_com(ast->functionCalls, $1);}
| function {push_back_com(ast->functions, $1);}
| if_expression {push_back_com(ast->if_expressions, $1);}
| while_expression {push_back_com(ast->cycles, $1);}
| for_expression {push_back_com(ast->cycles, $1);}
;

declaration:
  LET WORD ':' type init ';' { if ($5->type != OBJECT_TYPE) {
                                 if ($5->type != getValueType($4)) {
                                  printf("Incorrect type for %s\n", $2);
                                  YYABORT;
                                 }                           
                               }
                               struct member_type* mem = createMember(createValue(getValueType($4), $5->data), $2);
                               $$ = createCommand(num, mem); free($4);}
;

init:
  assignment {$$ = $1;}
| %empty {$$ = createValue(NULL_TYPE, NULL);}

initialization:
  WORD assignment ';' { struct member_type* mem = createMember($2, $1);
                        $$ = createCommand(num, mem);}
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
                           $$ = createCommand(num, f);}
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
                     push_back_mem($$, $1);}
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
                                                                          $$ = createCommand(num, (void*)res);}
;

functionImplementation:
  funcImpl                        { $$ = $1;}
| funcImpl functionImplementation { $$ = fullMergeAst($1, $2);}
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
;

brackets_functionImplementation:
  '{' functionImplementation '}' {$$ = $2;}
;

if_expression:
  IF expression brackets_functionImplementation else_expression {
                                                                  struct if_expr_type* res = createIfExpr($2, $3, $4);
                                                                  $$ = createCommand(num, (void*)res);
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
                                                      $$ = createCommand(num, (void*)res);}
;

for_expression:
  FOR WORD IN NUM TWO_POINTS NUM brackets_functionImplementation {int* a = calloc(16, sizeof(int));*a = $4;
                                                                  int* b = calloc(16, sizeof(int));*b = $6;
                                                                  push_back_com(ast->declarations, 
                                                                  createCommand(num, (struct command_type*)createMember(createValue(INTEGER_TYPE,a),$2)));
                                                                  struct cycle_type* res = createCycle(createIfCond(strdup("<="),
                                                                  createValue(OBJECT_TYPE,$2),createValue(INTEGER_TYPE,b)), $7);num++;
                                                                  $$ = createCommand(num, (void*)res);}
;

expr:
  second '+' expr {$$ = getOp($1, $3, "+"); if ($$ == NULL) {YYABORT;}}
| second '-' expr {$$ = getOp($1, $3, "-"); if ($$ == NULL) {YYABORT;}}
| second          {$$ = $1;}
;

second:
  val '*' second {$$ = getOp($1, $3, "*"); if ($$ == NULL) {YYABORT;}}
| val '/' second {$$ = getOp($1, $3, "/"); if ($$ == NULL) {YYABORT;}}
| val            {$$ = $1;}
;

%%

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}