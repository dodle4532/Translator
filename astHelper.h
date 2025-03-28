struct command_vec* sortAst(struct ast* ast);
struct command_type* findValue(struct ast* ast, char* name);
struct value_type* getValue(struct command_type* com);
struct value_type* getValueFromStr(char* str);
int getIntRes(int l, int r, char op);
float getFloatRes(float l, float r, char op);
struct value_type* getOp(struct value_type* left, struct value_type* right, char op);
char* getValFromValueType(struct value_type* val);
struct value_type* getDataFromObject(struct ast* ast, struct member_type* mem);
struct value_type* getDataFromFunc(struct ast* ast, struct func_call_type* call);
bool transformAst(struct ast* ast);
bool doFunc(struct ast* ast, struct command_type* com);
bool doIf(struct ast* ast, struct command_type* com);
bool doCycle(struct ast* ast, struct command_type* com);
int checkExpression(struct value_type* leftVal, struct value_type* rightVal, char* cmpChar);
bool checkEquality(struct value_type* leftVal, struct value_type* rightVal);
int checkMore(struct value_type* leftVal, struct value_type* rightVal);
int checkLess(struct value_type* leftVal, struct value_type* rightVal);
struct ast* mergeAst(struct ast* first, struct ast* second);
struct ast* createAstToDoWVal(struct ast* source, struct ast* toDo, int n);
struct ast* createAstToDoWOVal(struct ast* source, struct ast* toDo, int n);
struct ast* createAstToFunc(struct ast* source, struct ast* toDo);
bool doAst(struct ast* ast);
bool doAllAst(struct ast* ast);
int getMaxNum(struct ast* ast);
void changeNum(struct ast* ast, struct command_type* com);

void freeAst(struct ast* ast);
void free_value_vec(struct value_vec* vec);
void free_member_vec(struct member_vec* vec);
void free_func_impl(struct func_impl_type* func_impl);
void free_command_vec(struct command_vec* vec);

void printData(struct value_type* val);