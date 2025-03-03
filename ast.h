#include <stdlib.h>

enum VALUE_TYPE
{
  OBJECT_TYPE,
//  ARRAY_TYPE,
  STRING_TYPE,
//  NUMBER_TYPE,
  INTEGER_TYPE,
//  BOOLEAN_TYPE,
  NULL_TYPE
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
	struct ast* astWOfuncImpl;
};

struct func_impl_vec {
	struct func_impl_type** functions;
    size_t size;
    size_t capacity;
};

struct command_type {
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
    struct func_impl_vec* functions;
    struct command_vec* if_expressions;
};

struct value_type* createValue(enum VALUE_TYPE type, void* data); 
struct member_type* createMember(struct value_type* val, char* name);
struct command_type* createCommand(int num, void* command);
struct func_impl_type* createFuncImpl(char* name, struct member_vec* parametrs, struct ast* astWOfuncImpl);
struct member_vec* createMemberVec();
struct value_vec* createValueVec();
struct command_vec* createCommandVec();
struct func_impl_vec* createFuncImplVec();
struct func_call_type* createFuncCall(char* name, struct value_vec* values);
struct ast* createAst();
void push_back_mem(struct member_vec* mem, struct member_type* member);
void push_back_val(struct value_vec* val, struct value_type* value);
void push_back_com(struct command_vec* com, struct command_type* command);
void push_back_fImpl(struct func_impl_vec* fImpl, struct func_impl_type* functionImplementation);
void mergeAst(struct ast* first, struct ast* second);