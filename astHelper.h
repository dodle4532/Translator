struct command_vec* sortAst(struct ast* ast);
struct command_type* findValue(struct ast* ast, char* name);
struct value_type* getValue(struct command_type* com);
bool transformAst(struct ast* ast);