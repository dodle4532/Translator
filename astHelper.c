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