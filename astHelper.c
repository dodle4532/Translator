#include "ast.h"
#include "astHelper.h"
#include <stdio.h>
#include <string.h>

void quickSort(struct command_type** numbers, int left, int right)
{
    struct command_type* pivot; // разрешающий элемент
    int index; // индекс разрешающего элемента
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] > pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            left++; // сдвигаем левую границу вправо
        }
        while ((numbers[left] < pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            right--; // сдвигаем правую границу влево
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    index = left; 
    left = l_hold;
    right = r_hold;
    if (left < index) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(numbers, left, index - 1);
    if (right > index)
        quickSort(numbers, index + 1, right);
}


struct command_vec* sortAst(struct ast* ast) {
    struct command_vec* res = createCommandVec();
    for (int i = 0; i < ast->cycles->size; ++i) {
        push_back_com(res, ast->cycles->commands[i]);
    }
    for (int i = 0; i < ast->initializations->size; ++i) {
        push_back_com(res, ast->initializations->commands[i]);
    }
    for (int i = 0; i < ast->declarations->size; ++i) {
        push_back_com(res, ast->declarations->commands[i]);
    }
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        push_back_com(res, ast->functionCalls->commands[i]);
    }
    for (int i = 0; i < ast->functions->size; ++i) {
        push_back_com(res, ast->functions->commands[i]);
    }
    for (int i = 0; i < ast->if_expressions->size; ++i) {
        push_back_com(res, ast->if_expressions->commands[i]);
    }

    quickSort(res->commands, 0, res->size-1);
    return res;
}

struct command_type* findValue(struct ast* ast, char* name) {
    for (int i = 0; i < ast->declarations->size; ++i) {
        struct member_type* mem = ast->declarations->commands[i]->command;
        if (!strcmp(name, mem->name)) {
            return ast->declarations->commands[i];
        }
    }
    return NULL;
}

struct value_type* getValue(struct command_type* com) {
    if (!com) {
        return NULL;
    }
    struct member_type* mem = com->command;
    return mem->value;
}

bool transformAst(struct ast* ast) {
    for (int i = 0; i < ast->declarations->size; ++i) {
        for (int j = i + 1; j < ast->declarations->size; ++j) {
            struct member_type* mem1 = ast->declarations->commands[i]->command;
            struct member_type* mem2 = ast->declarations->commands[j]->command;
            if (!strcmp(mem1->name, mem2->name)) {
                printf("Redeclaration of %s in %d line\n", mem1->name, ast->declarations->commands[j]->num);
                return false;
            }
        }
    }
    for (int i = 0; i < ast->initializations->size; ++i) {
        int num = ast->initializations->commands[i]->num;
        struct member_type* mem = ast->initializations->commands[i]->command;
        struct command_type* com = findValue(ast, mem->name);
        struct value_type* val = getValue(com);
        if (!com || num < com->num) {
            printf("No such variable - %s in %d line", mem->name, num);
            return false;
        }
        if (mem->value->type != val->type) {
            printf("Incompletable types: trying to init %s to %s in %d line", getStrFromValueType(mem->value->type),
            getStrFromValueType(val->type), num);
            return false;
        }
        free(val->data);
        val->data = mem->value->data;
    }
    return true;
}

char* getValFromValueType(struct value_type* val) {
    if (val->type == NULL_TYPE || val->type == STRING_TYPE || val->type == OBJECT_TYPE) {
      return strdup((char*)val->data);
    } 
    if (val->type == INTEGER_TYPE) {
        char* res = calloc(16, sizeof(char));
        sprintf(res, "%d", *(int*)val->data);
        return res;
    }
    return NULL;
}

void deleteValFromAst(struct ast* ast, char* name) {
    for (int i = 0; i < ast->declarations->size; ++i) {
        struct member_type* mem = ast->declarations->commands[i]->command;
        if (!strcmp(name, mem->name)) {
            free(mem->name);
            mem->name = calloc(16, sizeof(char));
        }
    }
    return;
}

bool doFunc(struct ast* ast, struct func_call_type* call) {
    char* name = call->name;
    if (!strcmp(name, "println!")) {
        char* tmp = calloc(256, sizeof(char));
        int size = 0;
        for (int i = 0; i < call->values->size; ++i) {
            if (call->values->values[i]->type != STRING_TYPE) {
                printf("Invalid argument for func call %s", name);
                return false;
            }
            strcat(tmp, (char*)(call->values->values[i]->data));
            size += strlen((char*)(call->values->values[i]->data));
        }
        char* tmpToFree = tmp;
        char* res = calloc(512, sizeof(char));
        char* placeholder_location = strstr(tmp, "{");
        while (placeholder_location != NULL) {
            int prefix_length = placeholder_location - tmp + 1;
            char* value = calloc(32, sizeof(char));
            int t = 0;
            for (int i = prefix_length; i < 256; ++i) {
                t++;
                if (tmp[i] == ' ') {
                    continue;
                }
                if (tmp[i] == '}') {
                    break;
                }
                value[i - prefix_length] = tmp[i];
            }
            strncat(res, tmp, prefix_length-1);
            struct command_type* com = findValue(ast, value);
            if (!com) {
                printf("Undefined reference to %s", value);
                return false;
            }
            char* str = getValFromValueType(getValue(com));
            strcat(res, str); // ошибка когда bool
            tmp += prefix_length + t;
            size -= prefix_length + t;
            free(str);
            placeholder_location = strstr(tmp, "{");
        }
        strncat(res, tmp, size);
        printf("%s", res);
        free(res);
        free(tmpToFree);
        return true;
    }
    struct func_impl_type* impl;
    bool isFind = false;
    for (int i = 0; i < ast->functions->size; ++i) {
        impl = ast->functions->commands[i]->command;
        if (!strcmp(name, impl->name)) {
            isFind = true;
            break;
        }
    }
    if (!isFind) {
        printf("Implementation of funciton %s not found", name);
        return false;
    }
    if (!transformAst(impl->impl)) {
        return false;
    }
    struct ast* mergedAst = fullMergeAst(ast, impl->impl);
    if (impl->parametrs->size != call->values->size) {
        printf("Incorrect number of arguments in function call %s, should be %d, but there is %d",
                impl->name, impl->parametrs->size, call->values->size);
        return false;
    }
    for (int i = 0; i < impl->parametrs->size; ++i) {
        struct value_type* val = call->values->values[i];
        if (val->type == OBJECT_TYPE) {
            struct command_type* com = findValue(mergedAst, val->data);
            if (!com) {
                printf("%s not found\n", val->data);
                return false;
            }
            val = getValue(com);
        }
        if (val->type != impl->parametrs->members[i]->value->type) {
            printf("Incorrect type of parametr %s in function call %s, shoulde be %s, but there is %s",
                    impl->parametrs->members[i]->name, call->name, getStrFromValueType(impl->parametrs->members[i]->value->type),
                    getStrFromValueType(val->type));
            return false;
        }
        struct member_type* mem = createMember(val, impl->parametrs->members[i]->name);
        // printf("%s=%d\n",mem->name, *(int*)mem->value->data);
        struct command_type* com = createCommand(0, (void*)mem);
        deleteValFromAst(mergedAst, impl->parametrs->members[i]->name);
        push_back_com(mergedAst->declarations, com);
    }
    for (int i = 0; i < impl->impl->functionCalls->size; ++i) {
        struct value_vec* newParametrs = createValueVec();
        struct func_call_type* c = impl->impl->functionCalls->commands[i]->command;
        for (int j = 0; j < c->values->size; ++j) {
            struct value_type* val = c->values->values[j];
            // printf("%d\n", *(int*)val->data);
            if (val->type != OBJECT_TYPE) {
                push_back_val(newParametrs, val);
            }
            else {
                for (int i = 0; i < mergedAst->declarations->size; ++i) {
                    struct member_type* mem = mergedAst->declarations->commands[i]->command;
                    // if (!strcmp(mem->name, (char*)val->data)) {
                    //     //free(mem->value);
                    //     mem->value = 
                    //     break;
                    // }
                    // printf("---%s %d\n", mem->name, *(int*)mem->value->data);
                }
                struct command_type* com = findValue(mergedAst, (char*)val->data);
                if (!com) {
                    printf("Not found value %s", val->data);
                    return false;
                }
                push_back_val(newParametrs, getValue(com));
            }
        }
        struct value_vec* tmp = c->values;
        c->values = newParametrs;
        if (!doFunc(mergedAst, c)) {
            return false;
        }
        c->values = tmp;
        // free_value_vec(newParametrs);
    }
    return true;
}

bool doAllFunc(struct ast* ast) {
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        struct func_call_type* f = ast->functionCalls->commands[i]->command;
        bool res = doFunc(ast, f);
        if (!res) {
            return false;
        }
    }
    return true;
}

struct value_type* getValueFromIfCond(struct ast* ast, struct value_type* val) { // Попробовать использовать в doFunc
    if (val->type == OBJECT_TYPE) {
        struct command_type* com = findValue(ast, (char*)val->data);
        if (!com) {
            printf("%s not found\n", val->data);
            return NULL;
        }
        return getValue(com);
    }
    return val;
}

bool checkEquality(struct value_type* leftVal, struct value_type* rightVal) {
    if (leftVal->type == INTEGER_TYPE) {
        if (*(int*)leftVal->data == *(int*)rightVal->data) {
            return true;
        }
        return false;
    }
    if (leftVal->type == FLOAT_TYPE) {
        if (*(float*)leftVal->data == *(float*)rightVal->data) {
            return true;
        }
        return false;
    }
    if (leftVal->type == BOOLEAN_TYPE) {
        if (*(int*)leftVal->data == *(int*)rightVal->data) {
            return true;
        }
        return false;
    }
    if (leftVal->type == STRING_TYPE) {
        if (!strcmp((char*)leftVal->data, (char*)rightVal->data)) {
            return true;
        }
        return false;
    }
    return false;
}

int checkExpression(struct value_type* leftVal, struct value_type* rightVal, char* cmpChar) {
    if (leftVal->type != rightVal->type) {
        printf("Trying to check equality of %s and %s, which is not allowed\n", 
                getStrFromValueType(leftVal->type), getStrFromValueType(rightVal->type));
        return -1;
    }
    if (!strcmp(cmpChar, "==")) {
        return checkEquality(leftVal, rightVal);
    }
    if (!strcmp(cmpChar, "!=")) {
        return !checkEquality(leftVal, rightVal);
    }
    return -1;
}

bool doIf(struct ast* ast, struct if_expr_type* expr) {
    struct if_cond_type* cond = expr->cond;
    struct value_type* leftVal = getValueFromIfCond(ast, cond->leftVal);
    if (!leftVal) {
        return false;
    }
    struct value_type* rightVal = getValueFromIfCond(ast, cond->rightVal);
    if (!rightVal) {
        return false;
    }
    int res = checkExpression(leftVal, rightVal, cond->cmpChar);
    struct ast* mergedAst;
    switch (res)
    {
    case -1:
        return false;
    case 0:
        mergedAst = smallMergeAst(ast, expr->_else->body);
        doAst(mergedAst);
        return false;
    case 1:
        mergedAst = smallMergeAst(ast, expr->body);
        doAst(mergedAst);
        return true;
    default:
        return false;
    }
}

bool doAst(struct ast* ast) { // void
    if (!transformAst(ast)) {
        return 1;
    }
    if (!doAllFunc(ast)) {
        printf(" in line\n");
        return 1;
    }
    for (int i = 0; i < ast->if_expressions->size; ++i) {
        struct if_expr_type* expr = (struct if_expr_type*)ast->if_expressions->commands[i]->command;
        if (!doIf(ast, expr)) {
            return 1;
        }
    }
    return true;
}

struct ast* fullMergeAst(struct ast* first, struct ast* second) {
    struct ast* ast = createAst();
    for (int i = 0; i < first->declarations->size; ++i) {
        push_back_com(ast->declarations, first->declarations->commands[i]);
    }
    
    for (int i = 0; i < first->initializations->size; ++i) {
        push_back_com(ast->initializations, first->initializations->commands[i]);
    }
    
    for (int i = 0; i < first->functionCalls->size; ++i) {
        push_back_com(ast->functionCalls, first->functionCalls->commands[i]);
    }
    
    for (int i = 0; i < first->if_expressions->size; ++i) {
        push_back_com(ast->if_expressions, first->if_expressions->commands[i]);
    }
    
    for (int i = 0; i < first->functions->size; ++i) {
        push_back_com(ast->functions, first->functions->commands[i]);
    }
    
    for (int i = 0; i < first->cycles->size; ++i) {
        push_back_com(ast->cycles, first->functionCalls->commands[i]);
    }
    
    
    for (int i = 0; i < second->declarations->size; ++i) {
        push_back_com(ast->declarations, second->declarations->commands[i]);
    }

    for (int i = 0; i < second->initializations->size; ++i) {
        push_back_com(ast->initializations, second->initializations->commands[i]);
    }
    
    for (int i = 0; i < second->functionCalls->size; ++i) {
        push_back_com(ast->functionCalls, second->functionCalls->commands[i]);
    }
    
    for (int i = 0; i < second->if_expressions->size; ++i) {
        push_back_com(ast->if_expressions, second->if_expressions->commands[i]);
    }
    
    for (int i = 0; i < second->cycles->size; ++i) {
        push_back_com(ast->cycles, second->cycles->commands[i]);
    }

    return ast;
}

struct ast* smallMergeAst(struct ast* first, struct ast* second) {
    struct ast* ast = createAst();
    for (int i = 0; i < first->declarations->size; ++i) {
        push_back_com(ast->declarations, first->declarations->commands[i]);
    }
    
    for (int i = 0; i < first->initializations->size; ++i) {
        push_back_com(ast->initializations, first->initializations->commands[i]);
    }
    
    // for (int i = 0; i < first->functionCalls->size; ++i) {
    //     push_back_com(ast->functionCalls, first->functionCalls->commands[i]);
    // }

    for (int i = 0; i < first->functions->size; ++i) {
        push_back_com(ast->functions, first->functions->commands[i]);
    }
        
    
    for (int i = 0; i < second->declarations->size; ++i) {
        push_back_com(ast->declarations, second->declarations->commands[i]);
    }

    for (int i = 0; i < second->initializations->size; ++i) {
        push_back_com(ast->initializations, second->initializations->commands[i]);
    }
    
    for (int i = 0; i < second->functionCalls->size; ++i) {
        push_back_com(ast->functionCalls, second->functionCalls->commands[i]);
    }
    
    for (int i = 0; i < second->if_expressions->size; ++i) {
        push_back_com(ast->if_expressions, second->if_expressions->commands[i]);
    }
    
    for (int i = 0; i < second->cycles->size; ++i) {
        push_back_com(ast->cycles, second->cycles->commands[i]);
    }

    return ast;
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
                                    func_call->name = NULL;
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
                        if (!func_impl) free_func_impl(func_impl);
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