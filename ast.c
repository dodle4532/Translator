#include "ast.h"
#include <stdio.h>
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

struct command_type* createCommand(int num, void* command) {
    struct command_type* com = calloc(1, sizeof(struct command_type));
    com->num = num;
    com->command = command;
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


void mergeAst(struct ast* first, struct ast* second) {
    for (int i = 0; i < second->declarations->size; ++i) {
        push_back_com(first->declarations, second->declarations->commands[i]);
    }
    
    for (int i = 0; i < second->initializations->size; ++i) {
        push_back_com(first->initializations, second->initializations->commands[i]);
    }
    
    for (int i = 0; i < second->functionCalls->size; ++i) {
        push_back_com(first->functionCalls, second->functionCalls->commands[i]);
    }
    
    for (int i = 0; i < second->if_expressions->size; ++i) {
        push_back_com(first->if_expressions, second->if_expressions->commands[i]);
    }
    return;
}

void free_value_vec(struct value_vec* vec) {
    if (vec) {
        if (vec->values) {
            for (size_t i = 0; i < vec->size; ++i) {
                if (vec->values[i]) {
                  if(vec->values[i]->data){
                      free(vec->values[i]->data);
                  }
                  free(vec->values[i]);
                }
            }
            free(vec->values);
        }
        free(vec);
    }
}

void free_member_vec(struct member_vec* vec) {
    if (vec) {
        if (vec->members) {
            for (size_t i = 0; i < vec->size; ++i) {
                if (vec->members[i]) {
                    if (vec->members[i]->name) {
                        free(vec->members[i]->name);
                    }
                    if (vec->members[i]->value) {
                        if(vec->members[i]->value->data){
                            free(vec->members[i]->value->data);
                        }
                        free(vec->members[i]->value);
                    }
                    free(vec->members[i]);
                }
            }
            free(vec->members);
        }
        free(vec);
    }
}

void free_func_impl(struct func_impl_type* func_impl) {
    if (func_impl) {
        if(func_impl->name){
            free(func_impl->name);
        }

        if(func_impl->parametrs){
            free_member_vec(func_impl->parametrs);
        }

        if(func_impl->impl){
            freeAst(func_impl->impl);
        }
        if(func_impl->returnValue){
            if(func_impl->returnValue->data){
                free(func_impl->returnValue->data);
            }
            free(func_impl->returnValue);
        }

        free(func_impl);
    }
}

void free_command_vec(struct command_vec* vec, int n) {
    if (vec) {
        if (vec->commands) {
            for (size_t i = 0; i < vec->size; ++i) {
                if (vec->commands[i]) {
                    // Determine the type of command and free accordingly
                    switch (n) {
                        case 1: // Assuming 1 is for declarations (value_type)
                            if (vec->commands[i]->command) {
                                struct value_type* val = (struct value_type*)vec->commands[i]->command;
                                if(val->data){
                                    free(val->data);
                                }
                                free(val);
                            }
                            break;
                        case 2: // Assuming 2 is for initializations (value_type)
                            if (vec->commands[i]->command) {
                                struct value_type* val = (struct value_type*)vec->commands[i]->command;
                                if(val->data){
                                    free(val->data);
                                }
                                free(val);
                            }
                            break;
                        case 3: // Assuming 3 is for function calls (func_call_type)
                            if (vec->commands[i]->command) {
                                struct func_call_type* func_call = (struct func_call_type*)vec->commands[i]->command;
                                if (func_call->name) {
                                    free(func_call->name);
                                }
                                if (func_call->values) {
                                    free_value_vec(func_call->values);
                                }
                                free(func_call);
                            }
                            break;
                        case 4: // Assuming 4 is for functions (func_impl_type)
                            // Functions are freed by the free_func_impl_vec
                            break;
                        case 5: // Assuming 5 is for if_expressions (if_expr_type)
                            if (vec->commands[i]->command) {
                                struct if_expr_type* if_expr = (struct if_expr_type*)vec->commands[i]->command;
                                if (if_expr->cond) {
                                    if(if_expr->cond->cmpChar){
                                        free(if_expr->cond->cmpChar);
                                    }
                                    if (if_expr->cond->leftVal) {
                                        if(if_expr->cond->leftVal->data){
                                          free(if_expr->cond->leftVal->data);
                                        }
                                        free(if_expr->cond->leftVal);
                                    }
                                    if (if_expr->cond->rightVal) {
                                        if(if_expr->cond->rightVal->data){
                                          free(if_expr->cond->rightVal->data);
                                        }
                                        free(if_expr->cond->rightVal);
                                    }
                                    free(if_expr->cond);
                                }
                                if (if_expr->body) {
                                    freeAst(if_expr->body);
                                }
                                if (if_expr->_else) {
                                    freeAst(if_expr->_else->body);
                                    free(if_expr->_else);
                                }

                                free(if_expr);
                            }
                            break;
                         case 6: // Assuming 6 is for cycles (cycle_type)
                            if (vec->commands[i]->command) {
                                struct cycle_type* cycle = (struct cycle_type*)vec->commands[i]->command;
                                if (cycle->expr) {
                                     if(cycle->expr->cmpChar){
                                        free(cycle->expr->cmpChar);
                                    }
                                    if (cycle->expr->leftVal) {
                                         if(cycle->expr->leftVal->data){
                                              free(cycle->expr->leftVal->data);
                                         }
                                        free(cycle->expr->leftVal);
                                    }
                                    if (cycle->expr->rightVal) {
                                        if(cycle->expr->rightVal->data){
                                          free(cycle->expr->rightVal->data);
                                        }
                                        free(cycle->expr->rightVal);
                                    }
                                    free(cycle->expr);
                                }
                                if (cycle->body) {
                                    freeAst(cycle->body);
                                }
                                if (cycle->par) {
                                  free(cycle->par);
                                }
                                free(cycle);
                            }
                            break;

                        default:
                            printf("Unknown command type: %d\n", vec->commands[i]->num);
                            break;
                    }
                    free(vec->commands[i]);
                }
            }
            free(vec->commands);
        }
        free(vec);
    }
}


void freeAst(struct ast* ast) {
    if (ast) {
        if (ast->declarations) {
            free_command_vec(ast->declarations, 1);
        }
        if (ast->initializations) {
            free_command_vec(ast->initializations, 2);
        }
        if (ast->functionCalls) {
            free_command_vec(ast->functionCalls, 3);
        }
        if (ast->functions) {
            // First, get the command_vec
            struct command_vec* func_command_vec = ast->functions;
            // Check if commands exist in command_vec
            if (func_command_vec && func_command_vec->commands) {
                // Iterate through commands and extract func_impl_type
                for (size_t i = 0; i < func_command_vec->size; i++) {
                    if (func_command_vec->commands[i]) {
                        struct func_impl_type* func_impl = (struct func_impl_type*)func_command_vec->commands[i]->command;
                        free_func_impl(func_impl);
                        free(func_command_vec->commands[i]); // Освобождаем command_type

                    }
                }
                free(func_command_vec->commands); // Освобождаем массив commands
            }
            free(func_command_vec); // Освобождаем сам command_vec
        }
        if (ast->if_expressions) {
            free_command_vec(ast->if_expressions, 5);
        }
        if (ast->cycles) {
            free_command_vec(ast->cycles, 6);
        }
        free(ast);
    }
}