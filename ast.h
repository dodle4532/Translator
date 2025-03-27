#include <stdlib.h>

typedef enum {false, true} bool;

enum VALUE_TYPE
{
  STRING_TYPE,
  OBJECT_TYPE,
  FLOAT_TYPE,
  INTEGER_TYPE,
  BOOLEAN_TYPE,
  NULL_TYPE
};

enum COMMAND_TYPE
{
    VALUE_COM_TYPE,
    MEMBER_COM_TYPE,
    INIT_COM_TYPE,
    IF_COM_TYPE,
    CYCLE_COM_TYPE,
    FUNC_CALL_TYPE,
    FUNC_IMPL_TYPE
};

struct value_type
{
	enum VALUE_TYPE type;
	void *data;
};

struct member_type
{
	char *name;
	struct value_type *value;
};

struct value_vec {
    struct value_type** values;
    size_t size;
    size_t capacity;
};

struct member_vec {
    struct member_type** members;
    size_t size;
    size_t capacity;
};

struct func_call_type {
	char* name;
	struct value_vec* values;
};

struct func_impl_type {
	char* name;
	struct member_vec* parametrs;
	struct ast* impl;
    struct value_type* returnValue;
};

struct if_cond_type {
	char* cmpChar;
	struct value_type* leftVal;
	struct value_type* rightVal;
};

struct if_expr_type {
	struct if_cond_type* cond;
	struct ast* body;
	struct if_expr_type* _else;
};

struct cycle_type {
    struct if_cond_type* expr;
    struct ast* body;
    int* par;
};

struct command_type {
	enum COMMAND_TYPE type;
    int num;
	void* command;
};

struct command_vec {
	struct command_type** commands;
    size_t size;
    size_t capacity;
};

struct ast {
    struct command_vec* declarations;
    struct command_vec* initializations;
    struct command_vec* functionCalls;
    struct command_vec* functions;
    struct command_vec* if_expressions;
    struct command_vec* cycles;
};

const char* getStrFromValueType(enum VALUE_TYPE type);
struct value_type* createValue(enum VALUE_TYPE type, void* data); 
struct member_type* createMember(struct value_type* val, char* name);
struct command_type* createCommand(int num, enum COMMAND_TYPE type, void* command);
struct func_impl_type* createFuncImpl(char* name, struct member_vec* parametrs, struct ast* impl, struct value_type* returnValue);
struct if_expr_type* createIfExpr(struct if_cond_type* cond, struct ast* body, struct if_expr_type* _else);
struct if_cond_type* createIfCond(char* cmpChar, struct value_type* leftVal, struct value_type* rightVal);
struct cycle_type* createCycle(struct if_cond_type* expr, struct ast* body);
struct member_vec* createMemberVec();
struct value_vec* createValueVec();
struct command_vec* createCommandVec();
struct func_call_type* createFuncCall(char* name, struct value_vec* values);
struct ast* createAst();
void push_back_mem(struct member_vec* mem, struct member_type* member);
void push_back_val(struct value_vec* val, struct value_type* value);
void push_back_com(struct command_vec* com, struct command_type* command);