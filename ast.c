#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getStrFromValueType(enum VALUE_TYPE type) {
    switch (type)
    {
    case 0:
        return "str";
    case 1:
        return "obj";
    case 2:
        return "float";
    case 3:
        return "int";
    case 4:
        return "bool";
    case 5:
        return "null";
    default:
        break;
    }
    return "";
}

struct value_type* createValue(enum VALUE_TYPE type, void* data) {
    struct value_type* val = calloc(1, sizeof(struct value_type));
    val->data = data;
    val->type = type;
    return val;
}

struct member_type* createMember(struct value_type* val, char* name) {
    struct member_type* mem = calloc(1, sizeof(struct member_type));
    mem->name = name;
    mem->value = val;
    return mem;
}

struct command_type* createCommand(int num, enum COMMAND_TYPE type, void* command) {
    struct command_type* com = calloc(1, sizeof(struct command_type));
    com->command = command;
    com->type = type;
    com->num = num;
    return com;
}

struct func_impl_type* createFuncImpl(char* name, struct member_vec* parametrs, struct ast* impl, struct value_type* returnValue) {
    struct func_impl_type* res = calloc(1, sizeof(struct func_impl_type));
    res->name = name;
    res->parametrs = parametrs;
    res ->impl = impl;
    res->returnValue = returnValue;
    return res;
}

struct if_expr_type* createIfExpr(struct if_cond_type* cond, struct ast* body, struct if_expr_type* _else) {
    struct if_expr_type* res = calloc(1, sizeof(struct if_expr_type));
    res->cond = cond;
    res->body = body;
    res->_else = _else;
    return res;
}

struct if_cond_type* createIfCond(char* cmpChar, struct value_type* leftVal, struct value_type* rightVal) {
    struct if_cond_type* res = calloc(1, sizeof(struct if_cond_type));
    res->cmpChar = cmpChar;
    res->leftVal = leftVal;
    res->rightVal = rightVal;
    return res;
}

struct cycle_type* createCycle(struct if_cond_type* expr, struct ast* body) {
    struct cycle_type* res = calloc(1, sizeof(struct cycle_type));
    res->expr = expr;
    res->body = body;
    res->par = NULL;
    return res;
}

struct member_vec* createMemberVec() {
    struct member_vec* mem = calloc(1, sizeof(struct member_vec));
    mem->members = calloc(4, sizeof(struct member_type*));
    mem->size = 0;
    mem->capacity = 4;
    return mem;
}

struct value_vec* createValueVec() {
    struct value_vec* val = calloc(1, sizeof(struct value_vec));
    val->values = calloc(4, sizeof(struct value_type*));
    val->size = 0;
    val->capacity = 4;
    return val;
}

struct command_vec* createCommandVec() {
    struct command_vec* com = calloc(1, sizeof(struct command_vec));
    com->commands = calloc(128, sizeof(struct command_type*)); // попробовать 4
    com->size = 0;
    com->capacity = 4;
    return com;
}


struct func_call_type* createFuncCall(char* name, struct value_vec* values) {
    struct func_call_type* res = calloc(1, sizeof(struct func_call_type));
    res->name = calloc(64, sizeof(char));
    strcpy(res->name, name);
    res->values = values;
    return res;
}

struct ast* createAst() {
    struct ast* _ast = calloc(1, sizeof(struct ast));
    _ast->declarations = createCommandVec();
    _ast->initializations = createCommandVec();
    _ast->functionCalls = createCommandVec();
    _ast->functions = createCommandVec();
    _ast->if_expressions = createCommandVec();
    _ast->cycles = createCommandVec();
    return _ast;
}

void push_back_mem(struct member_vec* mem, struct member_type* member) {
    if (mem->size == mem->capacity) {
        // Необходимо увеличить вместимость
        size_t new_capacity = mem->capacity * 2;
        struct member_type** new_data = (struct member_type**)realloc(mem->members, new_capacity * sizeof(struct member_type*));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка перевыделения памяти для данных вектора\n");
            return; // Indicate failure
        }
        mem->members = new_data;
        mem->capacity = new_capacity;
    }

    mem->members[mem->size] = member;
    mem->size++;
    return;
}

void push_back_val(struct value_vec* val, struct value_type* value) {
    if (val->size == val->capacity) {
        // Необходимо увеличить вместимость
        size_t new_capacity = val->capacity * 2;
        struct value_type** new_data = (struct value_type**)realloc(val->values, new_capacity * sizeof(struct value_type*));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка перевыделения памяти для данных вектора\n");
            return; // Indicate failure
        }
        val->values = new_data;
        val->capacity = new_capacity;
    }

    val->values[val->size] = value;
    val->size++;
    return;
}

void push_back_com(struct command_vec* com, struct command_type* command) {
    if (com->size == com->capacity) {
        // Необходимо увеличить вместимость
        size_t new_capacity = com->capacity * 2;
        struct command_type** new_data = (struct command_type**)realloc(com->commands, new_capacity * sizeof(struct command_type*));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка перевыделения памяти для данных вектора\n");
            return; // Indicate failure
        }
        com->commands = new_data;
        com->capacity = new_capacity;
    }

    com->commands[com->size] = command;
    com->size++;
    return;
}