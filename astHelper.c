#include "ast.h"
#include "astHelper.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// В for i работает как переменная, а не должна

struct command_vec* helpCommandVec;

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
    // printf("-------\n");
    // for (int i = helpCommandVec->size - 1; i >= 0; i-=1) {
    //     struct member_type* mem = helpCommandVec->commands[i]->command;
    //     // printf("%s %d\n", mem->name, *(int*)mem->value->data);
    //     if (!strcmp(name, mem->name)) {
    //         return helpCommandVec->commands[i];
    //     }
    // }
    char* newName = strdup(name);
    strcat(newName, "+");
    for (int i = 0; i < ast->declarations->size; ++i) {
        struct member_type* mem = ast->declarations->commands[i]->command;
        if (!strcmp(newName, mem->name)) {
            return ast->declarations->commands[i];
        }
    }
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

int getIntRes(int l, int r, char op) {
    if (op == '+') {
        return l + r;
    }
    if (op == '-') {
        return l - r;
    }
    if (op == '*') {
        return l * r;
    }
    if (op == '/') {
        return l / r;
    }
}
float getFloatRes(float l, float r, char op) {
    if (op == '+') {
        return l + r;
    }
    if (op == '-') {
        return l - r;
    }
    if (op == '*') {
        return l * r;
    }
    if (op == '/') {
        return l / r;
    }
}
struct value_type* getOp(struct value_type* left, struct value_type* right, char op) {
    struct value_type* val = calloc(1, sizeof(struct value_type));
    if (left->type == INTEGER_TYPE && right->type == INTEGER_TYPE) {
        val->type = INTEGER_TYPE;
        int* a = malloc(sizeof(int));
        *a = getIntRes(*(int*)left->data, *(int*)right->data, op);
        val->data = a;
        // if (left->data != NULL) {
        //     free(left->data);
        // }
        // free(left);
        // if (right->data != NULL) {
        //     free(right->data);
        // }
        // free(right);
        return val;
    }
    if (left->type == FLOAT_TYPE && right->type == FLOAT_TYPE) {
        val->type = FLOAT_TYPE;
        float* a = malloc(sizeof(float));
        *a = getFloatRes(*(float*)left->data, *(float*)right->data, op);
        val->data = a;
        // if (left->data != NULL) {
        //     free(left->data);
        // }
        // free(left);
        // if (right->data != NULL) {
        //     free(right->data);
        // }
        // free(right);
        return val;
    }
    if (left->type == BOOLEAN_TYPE || right->type == BOOLEAN_TYPE || left->type == NULL_TYPE || right->type == NULL_TYPE) {
        free(val); return NULL;
    }
    if (left->type == OBJECT_TYPE || right->type == OBJECT_TYPE) {
        char* l1;
        char* l2;
        if (left->type == INTEGER_TYPE) {
            l1 = calloc(32,sizeof(char));
            sprintf(l1, "%d", *(int*)left->data);
            // free(left->data);
            // left->data = NULL;
        }
        else {
            l1 = (char*)left->data;
            if (left->type == STRING_TYPE) {
                strcat("'", l1);
            }
        }
        if (right->type == INTEGER_TYPE) {
            l2 = calloc(32,sizeof(char));
            sprintf(l2, "%d", *(int*)right->data);
            // free(right->data);
            // right->data = NULL;
        }
        else {
            l2 = (char*)right->data;
            if (right->type == STRING_TYPE) {
                char* tmp = calloc(32, sizeof(char));
                strcat(tmp, "'");
                strcat(tmp, l2);
                strcat(tmp, "'");
                free(l2);
                l2 = tmp;
            }
        }
        val->type = OBJECT_TYPE;
        char* o = calloc(1, sizeof(char));
        o[0] = op;
        strcat(l1, o); strcat(l1, l2); 
        free(o);
        val->data = l1;
        free(l2);
        return val;
    }
    if (op == '+') {
        free(val);
        return NULL;
    }
    if (left->type == STRING_TYPE && left->type == STRING_TYPE && op == '+') {
        strcat((char*) left->data, (char*)right->data);
        val->type = STRING_TYPE;
        val->data = strdup((char*)left->data);
        // free(right->data);
        // free(right);
        // free(left->data);
        // free(left);
        return val;
    }
    // if (left->data != NULL) {
    //   free(left->data);
    // }
    // free(left);
    // if (right->data != NULL) {
    //   free(right->data);
    // }
    // free(right);
    free(val);
    return NULL;
}

bool isInteger(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    // Пропускаем возможный знак
    if (*str == '-' || *str == '+') {
        str++;
    }

    // Проверяем, что остались только цифры
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Функция для проверки, является ли строка числом с плавающей точкой
bool isFloat(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    int dotCount = 0;
    // Пропускаем возможный знак
    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str != '\0') {
        if (*str == '.') {
            dotCount++;
            if (dotCount > 1) {
                return false; // Больше одной точки недопустимо
            }
        } else if (!isdigit(*str)) {
            return false;
        }
        str++;
    }

    // Должна быть хотя бы одна цифра
    return dotCount > 0 || isInteger(str);
}

// Функция для создания структуры value_type на основе строки
struct value_type* getValueFromStr(char* str) {
    struct value_type* result = (struct value_type*)calloc(1, sizeof(struct value_type));
    if (result == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return NULL;
    }

    // Проверяем на BOOL
    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
        result->type = BOOLEAN_TYPE;
        bool* boolValue = (bool*)calloc(4, sizeof(bool));
        *boolValue = (strcmp(str, "true") == 0) ? true : false;
        result->data = boolValue;
    }
    // Проверяем на INT
    else if (isInteger(str)) {
        result->type = INTEGER_TYPE;
        int* intValue = (int*)calloc(16, sizeof(int));
        *intValue = atoi(str);
        result->data = intValue;
    }
    // Проверяем на FLOAT
    else if (isFloat(str)) {
        result->type = FLOAT_TYPE;
        float* floatValue = (float*)calloc(16, sizeof(float));
        *floatValue = atof(str);
        result->data = floatValue;
    }
    else {
        size_t len = strlen(str);
        if (len > 2 && str[0] == '\'' && str[len - 1] == '\'') {  // STRING
            result->type = STRING_TYPE;
            char* stringValue = (char*)calloc(len, sizeof(char)); // -2 за кавычки + 1 за '\0'
            strcpy(stringValue, "\"");
            strncpy(stringValue, str + 1, len - 2); // Копируем без кавычек
            strcpy(stringValue, "\"");
            result->data = stringValue;
        } 
        else {  // OBJECT_TYPE
            result->type = OBJECT_TYPE;
            char* objectName = (char*)calloc(len, sizeof(char));
            strcpy(objectName, str);
            result->data = objectName;
        }
    }

    return result;
}
bool fillData(struct ast* ast, struct value_type* res, char* leftVal, char* rightVal, char op) {
    struct command_type* leftCom = findValue(ast, leftVal);
    if (!leftCom) {
        printf("%s not found", leftVal);
        return false;
    }
    struct member_type* leftMem = (struct member_type*)leftCom->command;
    struct value_type* left = leftMem->value;
    if (rightVal == NULL || rightVal[0] == 0) {
        if (res->type == NULL_TYPE) {
            res->type = left->type;
        }
        if (res->type != left->type) {
            printf("Trying to sign %s to %s", getStrFromValueType(left->type), getStrFromValueType(res->type)); 
            return false;   
        }
        res->data = left->data;
        return true;
    }
    struct value_type* right = getValueFromStr(rightVal);
    if (res->type != left->type) {
        printf("Trying to sign %s to %s", getStrFromValueType(left->type), getStrFromValueType(res->type)); 
        return false;   
    }
    if (right->type == OBJECT_TYPE) {
        struct command_type* rightCom = findValue(ast, rightVal);
        if (!rightCom) {
            printf("%s not found", rightVal);
            return false;
        }
        struct member_type* rightMem = (struct member_type*)rightCom->command;
        right = rightMem->value;
        // printData(right);
    }
    if (right->type != res->type) {
        printf("Trying to sign %s to %s", getStrFromValueType(right->type), getStrFromValueType(res->type)); 
        return false;  
    }
    // printData(res);
    res->data = getOp(res, right, op)->data;
    // left->data = res->data;
    // printData(res);
    return true;
}

bool transformAst(struct ast* ast) {
    for (int i = 0; i < ast->declarations->size; ++i) {
        struct member_type* mem1 = ast->declarations->commands[i]->command;
        for (int j = i + 1; j < ast->declarations->size; ++j) {
            struct member_type* mem2 = ast->declarations->commands[j]->command;
            if (!strcmp(mem1->name, mem2->name)) {
                printf("Redeclaration of %s in %d line\n", mem1->name, ast->declarations->commands[j]->num);
                return false;
            }
        }
        if (mem1->value->type == OBJECT_TYPE) {
            // printData(mem1->value);
            struct value_type* val = getDataFromObject(ast, mem1);
            if (val == NULL) {
                return false;
            }
            free(mem1->value);
            mem1->value = val;
            // printData(mem1->value);
        }
    }
    // free_command_vec(ast->initializations, 2);
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
    for (int i = 0; i < helpCommandVec->size; ++i) {
        struct member_type* mem = helpCommandVec->commands[i]->command;
        if (!strcmp(name, mem->name) && helpCommandVec->commands[i]->num == 0) {
            // free(mem->name);
            mem->name = calloc(16, sizeof(char));
            return;
        }
    }
    for (int i = 0; i < ast->declarations->size; ++i) {
        struct member_type* mem = ast->declarations->commands[i]->command;
        if (!strcmp(name, mem->name) && ast->declarations->commands[i]->num == 0) {
            free(mem->name);
            mem->name = calloc(16, sizeof(char));
            return;
        }
    }
    return;
}

bool doFunc(struct ast* ast, struct command_type* command) {
    struct func_call_type* call = (struct func_call_type*)command->command;
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
    // if (!transformAst(impl->impl)) {
    //     return false;
    // }
    struct ast* mergedAst = createAstToFunc(ast, impl->impl);
    if (impl->parametrs->size != call->values->size) {
        printf("Incorrect number of arguments in function call %s, should be %d, but there is %d\n",
                impl->name, impl->parametrs->size, call->values->size);
        return false;
    }
    for (int i = 0; i < impl->parametrs->size; ++i) {
        struct value_type* val = call->values->values[i];
        if (val->type == OBJECT_TYPE) {
            struct command_type* com = findValue(ast, val->data);
            if (!com) {
                printf("%s not found", val->data);
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
        // for (int i = 0; i < ast->declarations->size; ++i) {
        //     struct member_type* mem = ast->declarations->commands[i]->command;
        //     printf("%s\n", mem->name);
        // }
        char* newName = strdup(impl->parametrs->members[i]->name);
        strcat(newName, "+");
        struct member_type* mem = createMember(val, impl->parametrs->members[i]->name);
        // printf("%s=%d\n",mem->name, *(int*)mem->value->data);
        struct command_type* com = createCommand(0, MEMBER_COM_TYPE, (void*)mem);
        // deleteValFromAst(mergedAst, impl->parametrs->members[i]->name);
        push_back_com(mergedAst->declarations, com);
        // for (int i = 0; i < ast->declarations->size; ++i) {
        //     struct member_type* mem = ast->declarations->commands[i]->command;
        //     printf("%s\n", mem->name);
        // }
        // changeNum(mergedAst, com);
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
        
        // if (!doFunc(mergedAst, impl->impl->functionCalls->commands[i])) {
        //     return false;
        // }
        // for (int i = 0; i < impl->parametrs->size; ++i) {
        //     deleteValFromAst(mergedAst, impl->parametrs->members[i]->name);
        // }
        // free_value_vec(tmp);
        // free_value_vec(newParametrs);
    }
    return doAst(mergedAst);
}

struct value_type* getValueFromIfCond(struct ast* ast, struct value_type* val) { // Попробовать использовать в doFunc
    if (val->type == OBJECT_TYPE) {
        struct command_type* com = findValue(ast, (char*)val->data);
        if (!com) {
            printf("%s not found", val->data);
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

int checkLess(struct value_type* leftVal, struct value_type* rightVal) {
    if (!((leftVal->type == INTEGER_TYPE) || (leftVal->type == FLOAT_TYPE))) {
        printf("This operation is not allowed with %s type", getStrFromValueType(leftVal->type));
        return -1;
    }
    if (!((rightVal->type == INTEGER_TYPE) || (rightVal->type == FLOAT_TYPE))) {
        printf("This operation is not allowed with %s type", getStrFromValueType(rightVal->type));
        return -1;
    }
    if (leftVal->type == INTEGER_TYPE) {
        if (*(int*)leftVal->data < *(int*)rightVal->data) {
            return true;
        }
        return false;
    }
    if (leftVal->type == FLOAT_TYPE) {
        if (*(float*)leftVal->data < *(float*)rightVal->data) {
            return true;
        }
        return false;
    }
}

int checkMore(struct value_type* leftVal, struct value_type* rightVal) {
    if (!((leftVal->type == INTEGER_TYPE) || (leftVal->type == FLOAT_TYPE))) {
        printf("This operation is not allowed with %s type", getStrFromValueType(leftVal->type));
        return -1;
    }
    if (!((rightVal->type == INTEGER_TYPE) || (rightVal->type == FLOAT_TYPE))) {
        printf("This operation is not allowed with %s type", getStrFromValueType(rightVal->type));
        return -1;
    }
    if (leftVal->type == INTEGER_TYPE) {
        if (*(int*)leftVal->data > *(int*)rightVal->data) {
            return true;
        }
        return false;
    }
    if (leftVal->type == FLOAT_TYPE) {
        if (*(float*)leftVal->data > *(float*)rightVal->data) {
            return true;
        }
        return false;
    }
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
    if (!strcmp(cmpChar, "<")) {
        return checkLess(leftVal, rightVal);
    }
    if (!strcmp(cmpChar, ">")) {
        return checkMore(leftVal, rightVal);
    }
    if (!strcmp(cmpChar, ">=")) {
        return !checkLess(leftVal, rightVal);
    }
    if (!strcmp(cmpChar, "<=")) {
        return !checkMore(leftVal, rightVal);
    }
    return -1;
}

bool doIf(struct ast* ast, struct command_type* command) {
    struct if_expr_type* expr = (struct if_expr_type*)command->command;
    struct if_cond_type* cond = expr->cond;
    struct value_type* leftVal = getValueFromIfCond(ast, cond->leftVal);
    if (!leftVal) {
        printf(": Left value in if cond not found");
        return false;
    }
    struct value_type* rightVal = getValueFromIfCond(ast, cond->rightVal);
    if (!rightVal) {
        printf(": Right value in if cond not found");
        return false;
    }
    int res = checkExpression(leftVal, rightVal, cond->cmpChar);
    struct ast* mergedAst;
    switch (res)
    {
    case -1:
        return false;
    case 0:
        if (expr->_else == NULL) {
            return true;
        }
        mergedAst = createAstToDoWVal(ast, expr->_else->body, command->num);
        doAst(mergedAst);
        return true;
    case 1:
        mergedAst = createAstToDoWVal(ast, expr->body, command->num);
        return doAst(mergedAst);
    default:
        return false;
    }
}

bool doCycle(struct ast* ast, struct command_type* com) {
    struct cycle_type* cycle = com->command;
    int parIndex = -1;
    if (cycle->par != NULL) {
        parIndex = ast->declarations->size;
        push_back_com(ast->declarations, createCommand(com->num - 1, MEMBER_COM_TYPE, cycle->par));
    }
    struct value_type* leftVal = getValueFromIfCond(ast, cycle->expr->leftVal);
    if (!leftVal) {
        printf(": Left value in if cond not found");
        return false;
    }
    struct value_type* rightVal = getValueFromIfCond(ast, cycle->expr->rightVal);
    if (!rightVal) {
        printf(": Right value in if cond not found");
        return false;
    }
    int res = checkExpression(leftVal, rightVal, cycle->expr->cmpChar);
    while (res != 0) {
        if (res == -1) {
            return false;
        }
        struct ast* mergedAst = createAstToDoWVal(ast, cycle->body, com->num);
        if (!doAst(mergedAst)) {
            return false;
        }
        res = checkExpression(leftVal, rightVal, cycle->expr->cmpChar);
    }
    if (parIndex >= 0) {
        struct member_type* mem = (struct member_type*)ast->declarations->commands[parIndex]->command;
        strcat(mem->name, "-");
    }
    return true;
}

void printData(struct value_type* val) {
    if (val->type == INTEGER_TYPE) {
        printf("%d\n", *(int*)val->data);
    }
    else if (val->type == BOOLEAN_TYPE) {

    }
    else {
        printf("%s\n", val->data);
    }
    return;
}

struct value_type* getDataFromObject(struct ast* ast, struct member_type* mem) {
    char* data = mem->value->data;
    int index = 0;
    struct value_type* res = createValue(NULL_TYPE, NULL);
    char* leftVal = calloc(64, sizeof(char));
    char* rightVal = calloc(64, sizeof(char));
    char op = 0;
    bool isLeft = true;
    while (index < strlen(data)) {
        if (data[index] == '+' || data[index] == '-' || data[index] == '*' || data[index] == '*') {
            op = data[index];
            isLeft = false;
            if (!fillData(ast, res, leftVal, rightVal, op)) {
                return NULL;
            }
            index++;
            free(rightVal);
            rightVal = calloc(64, sizeof(char));
            continue;
        }
        if (isLeft) {
            leftVal[strlen(leftVal)] = data[index];
        }
        else {
            rightVal[strlen(rightVal)] = data[index];
        }
        index++;
    }
    if (!fillData(ast, res, leftVal, rightVal, op)) {
        return NULL;
    }
    return res;
}

bool doInit(struct ast* ast, struct command_type* command) {
    int num = command->num;
    struct member_type* mem = command->command;
    struct command_type* com = findValue(ast, mem->name);
    struct value_type* val = getValue(com);
    struct value_type* finalValue = mem->value;
    if (!com || num < com->num) {
        printf("No such variable - %s in %d line", mem->name, num);
        return false;
    }
    if (mem->value->type == OBJECT_TYPE) {
        finalValue = getDataFromObject(ast, mem);
        // printData(finalValue);
    }
    if (finalValue->type != val->type) {
        printf("Incompletable types: trying to init %s to %s in %d line", getStrFromValueType(finalValue->type),
        getStrFromValueType(val->type), num);
        return false;
    }
    if (val->data != finalValue->data) {
        // free(val->data);
        val->data = finalValue->data;
    }
    return true;
}

bool doCommand(struct ast* ast, struct command_type* com) {
    if (!com) {
        printf("Command not found\n");
        return false;
    }
    switch (com->type)
    {
    case IF_COM_TYPE:
        return doIf(ast, com);
    case FUNC_CALL_TYPE:
        return doFunc(ast, com);
    case CYCLE_COM_TYPE:
        return doCycle(ast, com);
    case INIT_COM_TYPE:
        return doInit(ast, com);
    // case MEMBER_COM_TYPE:
    //     struct member_type* mem = com->command;
    //     printData(mem->value);
    //     break;
    default:
        return true;
    }
}

bool doAst(struct ast* ast) { // void
    if (!transformAst(ast)) {
        return false;
    }
    struct command_vec* vec = sortAst(ast);
    for (int i = 0; i < vec->size; ++i) {
        if(!doCommand(ast, vec->commands[i])) {
            return false;
        }
    }
    return true;
}

bool doAllAst(struct ast* ast) {
    helpCommandVec = createCommandVec();
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        struct func_call_type* c = ast->functionCalls->commands[i]->command;
        if (!strcmp(c->name, "main")) {
            printf("You are not allowed to call main");
            return false;
        }
    } 
    push_back_com(ast->functionCalls, createCommand(getMaxNum(ast)+1, FUNC_CALL_TYPE, createFuncCall(strdup("main"), createValueVec())));
    int res = doAst(ast);
    free(helpCommandVec);
    return res;
}

int getMaxNum(struct ast* ast) {
    int num = 0;
    for (int i = 0; i < ast->cycles->size; ++i) {
        if (ast->cycles->commands[i]->num > num) {
            num = ast->cycles->commands[i]->num;
        }
        struct cycle_type* cycle = (struct cycle_type*) ast->cycles->commands[i]->command;
        int implMax = getMaxNum(cycle->body);
        if (implMax > num) {
            num = implMax;
        }
    }
    for (int i = 0; i < ast->initializations->size; ++i) {
        if (ast->initializations->commands[i]->num > num) {
            num = ast->initializations->commands[i]->num;
        }
    }
    for (int i = 0; i < ast->declarations->size; ++i) {
        if (ast->declarations->commands[i]->num > num) {
            num = ast->declarations->commands[i]->num;
        }
    }
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        if (ast->functionCalls->commands[i]->num > num) {
            num = ast->functionCalls->commands[i]->num;
        }
    }
    for (int i = 0; i < ast->functions->size; ++i) {
        if (ast->functions->commands[i]->num > num) {
            num = ast->functions->commands[i]->num;
        }
        struct func_impl_type* impl = (struct func_impl_type*) ast->functions->commands[i]->command;
        int implMax = getMaxNum(impl->impl);
        if (implMax > num) {
            num = implMax;
        }
    }
    for (int i = 0; i < ast->if_expressions->size; ++i) {
        if (ast->if_expressions->commands[i]->num > num) {
            num = ast->if_expressions->commands[i]->num;
        }
        struct if_expr_type* expr = (struct if_expr_type*) ast->if_expressions->commands[i]->command;
        int implMax = getMaxNum(expr->body);
        if (implMax > num) {
            num = implMax;
        }
    }
    return num;
}

void changeNum(struct ast* ast, struct command_type* com) {
    for (int i = 0; i < ast->cycles->size; ++i) {
        if (ast->cycles->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    for (int i = 0; i < ast->initializations->size; ++i) {
        if (ast->initializations->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    for (int i = 0; i < ast->declarations->size; ++i) {
        if (ast->declarations->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        if (ast->functionCalls->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    for (int i = 0; i < ast->functions->size; ++i) {
        if (ast->functions->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    for (int i = 0; i < ast->if_expressions->size; ++i) {
        if (ast->if_expressions->commands[i] == com) {
            com->num = getMaxNum(ast) + 1;
        }
    }
    return;
}

struct ast* mergeAst(struct ast* first, struct ast* second) {
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
        push_back_com(ast->cycles, first->cycles->commands[i]);
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
    
    for (int i = 0; i < second->functions->size; ++i) {
        push_back_com(ast->functions, second->functions->commands[i]);
    }
    
    for (int i = 0; i < second->cycles->size; ++i) {
        push_back_com(ast->cycles, second->cycles->commands[i]);
    }

    return ast;
}

struct ast* createAstToDoWVal(struct ast* source, struct ast* toDo, int n) {
    struct ast* ast = createAstToDoWOVal(source, toDo, n);
    for (int i = 0; i < source->declarations->size; ++i) {
        // if (source->declarations->commands[i]->num <= n) {
            push_back_com(ast->declarations, source->declarations->commands[i]);
        // }
    }
    return ast;
}

struct ast* createAstToDoWOVal(struct ast* source, struct ast* toDo, int n) {
    struct ast* ast = createAst();

    for (int i = 0; i < toDo->declarations->size; ++i) {
        // if (toDo->declarations->commands[i]->num <= n) {
            push_back_com(ast->declarations, toDo->declarations->commands[i]);
    
        // }
    }
    for (int i = 0; i < toDo->initializations->size; ++i) {
        // if (toDo->initializations->commands[i]->num <= n) {
            push_back_com(ast->initializations, toDo->initializations->commands[i]);
    
        // }
    }
    for (int i = 0; i < source->functions->size; ++i) {
        push_back_com(ast->functions, source->functions->commands[i]);
    }
    for (int i = 0; i < toDo->functionCalls->size; ++i) {
        // if (toDo->functionCalls->commands[i]->num >= n) {
            push_back_com(ast->functionCalls, toDo->functionCalls->commands[i]);
    
        // }
    }
    for (int i = 0; i < toDo->if_expressions->size; ++i) {
        // if (toDo->if_expressions->commands[i]->num >= n) {
            push_back_com(ast->if_expressions, toDo->if_expressions->commands[i]);
    
        // }
    }
    for (int i = 0; i < toDo->cycles->size; ++i) {
        // if (toDo->cycles->commands[i]->num >= n) {
            push_back_com(ast->cycles, toDo->cycles->commands[i]);
    
        // }
    }
    return ast;
}
 
struct ast* createAstToFunc(struct ast* source, struct ast* toDo) {
    struct ast* ast = createAst();

    for (int i = 0; i < toDo->declarations->size; ++i) {
        push_back_com(ast->declarations, toDo->declarations->commands[i]);
    }
    for (int i = 0; i < source->functions->size; ++i) {
        push_back_com(ast->functions, source->functions->commands[i]);
    }
    for (int i = 0; i < toDo->functionCalls->size; ++i) {
        push_back_com(ast->functionCalls, toDo->functionCalls->commands[i]);
    }
    for (int i = 0; i < toDo->if_expressions->size; ++i) {
        push_back_com(ast->if_expressions, toDo->if_expressions->commands[i]);
    }
    for (int i = 0; i < toDo->cycles->size; ++i) {
        push_back_com(ast->cycles, toDo->cycles->commands[i]);
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
                                vec->size = 0;
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