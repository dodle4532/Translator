#include "ast.h"
#include <stdio.h>

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

struct member_vec* createMembersVec() {
    struct member_vec* mem = calloc(1, sizeof(struct member_vec));
    mem->members = calloc(4, sizeof(struct member_type*));
    mem->size = 0;
    mem->capacity = 4;
    return mem;
}


struct ast* createAst() {
    struct ast* _ast = calloc(1, sizeof(struct ast));
    _ast->declarations = createMembersVec();
    _ast->functionCalls = createMembersVec();
    _ast->functions = createMembersVec();
    _ast->if_expression = createMembersVec();
    _ast->initializations = createMembersVec();
    return _ast;
}

void push_back(struct member_vec* mem, struct member_type* member) {
    if (mem->size == mem->capacity) {
        printf("ok");
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