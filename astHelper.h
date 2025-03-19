struct command_vec* sortAst(struct ast* ast);
struct command_type* findValue(struct ast* ast, char* name);
struct value_type* getValue(struct command_type* com);
bool transformAst(struct ast* ast);
bool doFunc(struct ast* ast, struct func_call_type* call);
char* getValFromValueType(struct value_type* val);
bool doAllFunc(struct ast* ast);
struct ast* mergeAst(struct ast* first, struct ast* second);


void freeAst(struct ast* ast);
void free_value_vec(struct value_vec* vec);
void free_member_vec(struct member_vec* vec);
void free_func_impl(struct func_impl_type* func_impl);
void free_command_vec(struct command_vec* vec, int n);