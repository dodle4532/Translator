struct command_vec* sortAst(struct ast* ast);
struct command_type* findValue(struct ast* ast, char* name);
struct value_type* getValue(struct command_type* com);
char* getValFromValueType(struct value_type* val);
bool transformAst(struct ast* ast);
bool doFunc(struct ast* ast, struct func_call_type* call);
bool doIf(struct ast* ast, struct if_expr_type* expr);
int checkExpression(struct value_type* leftVal, struct value_type* rightVal, char* cmpChar);
bool checkEquality(struct value_type* leftVal, struct value_type* rightVal);
bool doAllFunc(struct ast* ast);
struct ast* fullMergeAst(struct ast* first, struct ast* second);
struct ast* smallMergeAst(struct ast* first, struct ast* second);
bool doAst(struct ast* ast);


void freeAst(struct ast* ast);
void free_value_vec(struct value_vec* vec);
void free_member_vec(struct member_vec* vec);
void free_func_impl(struct func_impl_type* func_impl);
void free_command_vec(struct command_vec* vec, int n);