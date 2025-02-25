#include <stdlib.h>

enum VALUE_TYPE
{
//  OBJECT_TYPE,
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
  // the data pointer can be a primitive like a string, int, boolean or null
  // or to an array or object
  void *data;
};

struct member_type
{
  char *name;
  struct value_type *value;
};

struct member_vec {
    struct member_type** members;
    size_t size;
    size_t capacity;
};

struct ast
{
    struct member_vec* declarations;
    struct member_vec* initializations;
    struct member_vec* functionCalls;
    struct member_vec* functions;
    struct member_vec* if_expressions;
};

struct value_type* createValue(enum VALUE_TYPE type, void* data); 
struct member_type* createMember(struct value_type* val, char* name);
struct member_vec* createMembersVec();
struct ast* createAst();
void push_back(struct member_vec* mem, struct member_type* member);