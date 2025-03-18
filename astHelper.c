#include "ast.h"
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
                printf("Redeclaration of %s in %d\n", mem1->name, ast->declarations->commands[j]->num);
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
            printf("No such variable - %s in %d\n", mem->name, num);
            return false;
        }
        if (mem->value->type != val->type) {
            printf("Incompletable types: trying to init %s to %s in %d\n", getStrFromValueType(mem->value->type),
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

bool doFunc(struct ast* ast, struct func_call_type* call) {
    char* name = call->name;
    if (!strcmp(name, "println!")) {
        char* tmp = calloc(256, sizeof(char));
        int size = 0;
        for (int i = 0; i < call->values->size; ++i) {
            if (call->values->values[i]->type != STRING_TYPE) {
                printf("Invalid argument for func call %s\n", name);
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
                printf("Undefined reference to %s\n", value);
                return false;
            }
            char* str = getValFromValueType(getValue(com));
            strcat(res, str);
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
        }
    }
    if (!isFind) {
        printf("Implementation of funciton %s not found\n", name);
        return false;
    }
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