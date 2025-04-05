#include "ast.h"
#include "astHelper.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

bool isInFunc = false;
struct value_type* returnValue;
extern struct ast* globalAst;

extern struct ast* g_astCont[2048];
extern int g_astContSize;
struct command_vec* g_vecCont[256];
int g_vecContSize;


#define BUFFER_SIZE 10000

char output_buffer[BUFFER_SIZE]; // Буфер для хранения сообщений
int buffer_position = 0;       // Текущая позиция в буфере

// Функция для записи в буфер
void buffered_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  int bytes_written = vsnprintf(output_buffer + buffer_position, BUFFER_SIZE - buffer_position, format, args);

  va_end(args);

  if (bytes_written > 0) {
    buffer_position += bytes_written;
    if (buffer_position >= BUFFER_SIZE) {
      fprintf(stderr, "Warning: Output buffer overflow!\n");
      output_buffer[BUFFER_SIZE - 1] = '\0';
    }
  } else {
    fprintf(stderr, "Error: Failed to write to output buffer.\n");
  }
}

// Функция для вывода содержимого буфера на экран
void flush_buffer() {
  printf("%s", output_buffer);
  memset(output_buffer, 0, sizeof(output_buffer));
  buffer_position = 0;
}

void quickSort(struct command_type** numbers, int left, int right)
{
    struct command_type* pivot;
    int index;
    int l_hold = left;
    int r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] > pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] < pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;
    index = left; 
    left = l_hold;
    right = r_hold;
    if (left < index)
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
    g_vecCont[g_vecContSize++] = res;
    return res;
}

struct command_type* findValue(struct ast* ast, char* name) {
    if (!strcmp(name, "")) {
        return NULL;
    }

    bool isOp = false;
    for (int i = 0; i < strlen(name) - 1; ++i) {
        if (name[i] == '+' || name[i] == '-' || name[i] == '*' || name[i] == '*') {
            isOp = true;
            break;
        }
    } 
    struct value_type* val = NULL;
    struct member_type* mem = createMember(createValue(OBJECT_TYPE, name), name);
    if (isOp) {
        val = getDataFromObject(ast, mem);
        if (!val) {
            return NULL;
        }
        mem->value = val;
        return createCommand(0, MEMBER_COM_TYPE, mem);
    }
    bool isFunc = false;
    int count = 0; // Запятые
    for (int i = 0; i < strlen(name); ++i) {
        if (name[i] == '(') {
            isFunc = true;
        }
        if (name[i] == ',') {
            count++;
        }
    }
    if (isFunc) {
        struct value_vec* values = createValueVec();
        char* funcName = calloc(32, sizeof(char));
        char* value = calloc(32, sizeof(char));
        int index = 0;
        bool isPar = false;
        while (index < strlen(name)) {
            if (name[index] == '(') {
                isPar = true;
                index++;
                continue;
            }
            if (name[index] == ',') {
                push_back_val(values, getValueFromStr(value));
                free(value);
                value = calloc(32, sizeof(char));
                index++;
                continue;
            }
            if (name[index] == ')') {
                if (value) push_back_val(values, getValueFromStr(value));
                free(value);
                break;
            }
            if (!isPar) {
                funcName[index] = name[index]; 
            }
            else {
                value[strlen(value)] = name[index];
            }
            index++;
        }
        struct func_call_type* call = createFuncCall(funcName, values);
        val = getDataFromFunc(ast, call);
        if (!val) {
            return NULL;
        }
        mem->value = val;
        free(values->values); free(values);
        return createCommand(0, MEMBER_COM_TYPE, mem);
    }
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
        return val;
    }
    if (left->type == FLOAT_TYPE && right->type == FLOAT_TYPE) {
        val->type = FLOAT_TYPE;
        float* a = malloc(sizeof(float));
        *a = getFloatRes(*(float*)left->data, *(float*)right->data, op);
        val->data = a;
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
        }
        else if (left->type == FLOAT_TYPE) {
            l1 = calloc(32,sizeof(char));
            sprintf(l1, "%f", *(float*)left->data);
        }
        else if (left->type == STRING_TYPE) {
            char* tmp = calloc(32, sizeof(char));
            strcat(tmp, "'");
            strcat(tmp, l1);
            strcat(tmp, "'");
            free(l1);
            l1 = tmp;
        }
        else if (left->type == FUNC_TYPE) {
            l1 = calloc(32, sizeof(char));
            struct command_type* com = (struct command_type*)left->data;
            struct func_call_type* call = (struct func_call_type*)com->command;
            strcat(l1, call->name);
            strcat(l1, "(");
            for (int i = 0; i < call->values->size; ++i) {
                if (i > 0) strcat(l1, ",");
                strcat(l1, getStrFromValue(call->values->values[i]));
            }
            strcat(l1, ")");
        }
        else {
            l1 = (char*)left->data;
        }
        if (right->type == INTEGER_TYPE) {
            l2 = calloc(32,sizeof(char));
            sprintf(l2, "%d", *(int*)right->data);
        }
        else if (right->type == FLOAT_TYPE) {
            l2 = calloc(32,sizeof(char));
            sprintf(l2, "%f", *(float*)right->data);
        }
        else if (right->type == STRING_TYPE) {
            char* tmp = calloc(32, sizeof(char));
            strcat(tmp, "'");
            strcat(tmp, l2);
            strcat(tmp, "'");
            free(l2);
            l2 = tmp;
        }
        else if (right->type == FUNC_TYPE) {
            l2 = calloc(32, sizeof(char));
            struct command_type* com = (struct command_type*)right->data;
            struct func_call_type* call = (struct func_call_type*)com->command;
            strcat(l2, call->name);
            strcat(l2, "(");
            for (int i = 0; i < call->values->size; ++i) {
                if (i > 0)  strcat(l2, ",");
                strcat(l2, getStrFromValue(call->values->values[i]));
            }
            strcat(l2, ")");
        }
        else {
            l2 = (char*)right->data;
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
    if (left->type == STRING_TYPE && left->type == STRING_TYPE && op == '+') {
        strcat((char*) left->data, (char*)right->data);
        val->type = STRING_TYPE;
        val->data = strdup((char*)left->data);
        return val;
    }
    if (left->type == FUNC_TYPE || right->type == FUNC_TYPE) {
        char* l1;
        char* l2;
        if (left->type == INTEGER_TYPE) {
            l1 = calloc(32,sizeof(char));
            sprintf(l1, "%d", *(int*)left->data);
        }
        else if (left->type == FLOAT_TYPE) {
            l1 = calloc(32,sizeof(char));
            sprintf(l1, "%f", *(float*)left->data);
        }
        else if (left->type == FUNC_TYPE) {
            l1 = calloc(32, sizeof(char));
            struct command_type* com = (struct command_type*)left->data;
            struct func_call_type* call = (struct func_call_type*)com->command;
            strcat(l1, call->name);
            strcat(l1, "(");
            for (int i = 0; i < call->values->size; ++i) {
                if (i > 0) strcat(l1, ",");
                strcat(l1, getStrFromValue(call->values->values[i]));
            }
            strcat(l1, ")");
        }
        else if (left->type == STRING_TYPE) {
            char* tmp = calloc(32, sizeof(char));
            strcat(tmp, "'");
            strcat(tmp, l1);
            strcat(tmp, "'");
            free(l1);
            l1 = tmp;
        }
        else {
            l1 = (char*)left->data;
            
        }
        if (right->type == INTEGER_TYPE) {
            l2 = calloc(32,sizeof(char));
            sprintf(l2, "%d", *(int*)right->data);
        }
        else if (right->type == FLOAT_TYPE) {
            l2 = calloc(32,sizeof(char));
            sprintf(l2, "%f", *(float*)right->data);
        }
        else if (right->type == STRING_TYPE) {
            char* tmp = calloc(32, sizeof(char));
            strcat(tmp, "'");
            strcat(tmp, l2);
            strcat(tmp, "'");
            free(l2);
            l2 = tmp;
        }
        else if (right->type == FUNC_TYPE) {
            l2 = calloc(32, sizeof(char));
            struct command_type* com = (struct command_type*)right->data;
            struct func_call_type* call = (struct func_call_type*)com->command;
            strcat(l2, call->name);
            strcat(l2, "(");
            for (int i = 0; i < call->values->size; ++i) {
                if (i > 0)  strcat(l2, ",");
                strcat(l2, getStrFromValue(call->values->values[i]));
            }
            strcat(l2, ")");
        }
        else {
            l2 = (char*)right->data;
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
    struct value_type* leftVal = left;
    struct value_type* rightVal = right;
    if (leftVal == left && rightVal == right) {
        free(val);
        return NULL;
    }
    return getOp(leftVal, rightVal, op);
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

bool isFloat(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    int dotCount = 0;
    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str != '\0') {
        if (*str == '.') {
            dotCount++;
            if (dotCount > 1) {
                return false;
            }
        } else if (!isdigit(*str)) {
            return false;
        }
        str++;
    }

    return dotCount > 0 || isInteger(str);
}

// Функция для создания структуры value_type на основе строки
struct value_type* getValueFromStr(char* str) {
    struct value_type* result = (struct value_type*)calloc(1, sizeof(struct value_type));
    

    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
        result->type = BOOLEAN_TYPE;
        bool* boolValue = (bool*)calloc(4, sizeof(bool));
        *boolValue = (strcmp(str, "true") == 0) ? true : false;
        result->data = boolValue;
    }
    else if (isInteger(str)) {
        result->type = INTEGER_TYPE;
        int* intValue = (int*)calloc(16, sizeof(int));
        *intValue = atoi(str);
        result->data = intValue;
    }
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
            char* stringValue = (char*)calloc(len, sizeof(char));
            strcpy(stringValue, "\"");
            strncpy(stringValue, str + 1, len - 2);
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
    struct value_type* left = getValueFromStr(leftVal);
    if (left->type == OBJECT_TYPE) {
        struct command_type* leftCom = findValue(ast, leftVal);
        if (!leftCom) {
            error("%s not found", leftVal);
            return false;
        }
        struct member_type* leftMem = (struct member_type*)leftCom->command;
        if (leftMem->value->type == OBJECT_TYPE) {
            leftMem->value = getDataFromObject(ast, leftMem);
        }
        left->data = leftMem->value->data;
        left->type = leftMem->value->type;
    }
    if (left->type == FUNC_TYPE) {
        struct command_type* leftCom = (struct command_type*)left->data;
        struct func_call_type* call = (struct func_call_type*)leftCom->command;
        left = getDataFromFunc(ast, call);
        if (!left) {
            return false;
        }
    }
    if (res->type == NULL_TYPE) {
        res->type = left->type;
    }
    if (rightVal == NULL || rightVal[0] == 0) {
        if (res->type != left->type) {
            error("Trying to sign %s to %s", getStrFromValueType(left->type), getStrFromValueType(res->type)); 
            return false;   
        }
        res->data = left->data;
        return true;
    }
    struct value_type* right = getValueFromStr(rightVal);
    if (res->type != left->type) {
        error("Trying to sign %s to %s", getStrFromValueType(left->type), getStrFromValueType(res->type)); 
        return false;   
    }
    if (res->data == NULL) {
        res->data = left->data;
    }
    if (right->type == OBJECT_TYPE) {
        struct command_type* rightCom = findValue(ast, rightVal);
        if (!rightCom) {
            error("%s not found", rightVal);
            return false;
        }
        struct member_type* rightMem = (struct member_type*)rightCom->command;
        right = rightMem->value;
    }
    if (right->type != res->type) {
        error("Trying to sign %s to %s", getStrFromValueType(right->type), getStrFromValueType(res->type)); 
        return false;  
    }
    res->data = getOp(left, right, op)->data;
    return true;
}

struct value_type* getDataFromFunc(struct ast* ast, struct func_call_type* call) {
    char* name = call->name;
    if (!strcmp(name, "println!")) {
        error("You are not allowed to sign println! to object");
        return NULL;
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
        error("Implementation of funciton %s not found", name);
        return NULL;
    }
    struct ast* mergedAst = createAstToFunc(ast, impl->impl);
    if (impl->parametrs->size != call->values->size) {
        error("Incorrect number of arguments in function call %s, should be %d, but there is %d\n",
                impl->name, impl->parametrs->size, call->values->size);
        return NULL;
    }
    for (int i = 0; i < impl->parametrs->size; ++i) {
        struct value_type* val = call->values->values[i];
        if (val->type == OBJECT_TYPE) {
            struct command_type* com = findValue(ast, val->data);
            if (!com) {
                error("%s not found", val->data);
                return NULL;
            }
            val = getValue(com);
        }
        if (val->type != impl->parametrs->members[i]->value->type) {
            error("Incorrect type of parametr %s in function call %s, shoulde be %s, but there is %s",
                    impl->parametrs->members[i]->name, call->name, getStrFromValueType(impl->parametrs->members[i]->value->type),
                    getStrFromValueType(val->type));
            return NULL;
        }
        struct member_type* mem = createMember(val, impl->parametrs->members[i]->name);
        struct command_type* com = createCommand(0, MEMBER_COM_TYPE, (void*)mem);
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
                }
                struct command_type* com = findValue(mergedAst, (char*)val->data);
                if (!com) {
                    error("Not found value %s", val->data);
                    return NULL;
                }
                push_back_val(newParametrs, getValue(com));
            }
        }
        struct value_vec* tmp = c->values;
        c->values = newParametrs;
    }
    isInFunc = true;
    if (!doAst(mergedAst)) {
        return NULL;
    }
    if (returnValue == NULL) {
        error("Trying to sign void function %s to value", impl->name);
        return NULL;
    }
    if (returnValue->type != OBJECT_TYPE) {
        if (returnValue->type != impl->wantedReturnType) {
            error("Trying to return %s, but needed %s", getStrFromValueType(returnValue->type),
                                                         getStrFromValueType(impl->wantedReturnType));
            isInFunc = false;
            return NULL;
        }
        isInFunc = false;
        struct value_type* res = returnValue;
        returnValue = NULL;
        return res;
    }
    struct command_type* com = findValue(mergedAst, returnValue->data);
    if (!com) {
        error("Return value %s not found", returnValue->data);
        isInFunc = false;
        return NULL;
    }
    struct value_type* res = getValue(com);
    if (res->type != impl->wantedReturnType) {
        error("Trying to return %s, but needed %s", getStrFromValueType(res->type),
                                                     getStrFromValueType(impl->wantedReturnType));
        isInFunc = false;
        return NULL;
    }
    isInFunc = false;
    returnValue = NULL;
    return res;
}

bool checkAst(struct ast* ast) {
    for (int i = 0; i < ast->declarations->size; ++i) {
        if (ast->declarations->commands[i]->type == RETURN_TYPE) {
            continue;
        }
        struct member_type* mem1 = ast->declarations->commands[i]->command;
        for (int j = i + 1; j < ast->declarations->size; ++j) {
            struct member_type* mem2 = ast->declarations->commands[j]->command;
            if (!strcmp(mem1->name, mem2->name)) {
                error("Redeclaration of %s in %d line\n", mem1->name, ast->declarations->commands[j]->num);
                return false;
            }
        }
    }
    for (int i = 0; i < ast->initializations->size; ++i) {
        bool isFind = false;
        struct member_type* init = ast->initializations->commands[i]->command;
        for (int j = 0; j < ast->declarations->size; ++j) {
            struct member_type* decl = ast->declarations->commands[j]->command;
            if (!strcmp(decl->name, init->name)) {
                if (ast->declarations->commands[j]->num < ast->initializations->commands[i]->num) {
                    isFind = true;
                }
            }
        }
        if (!isFind) {
            error("Trying to init %s, but there is no declaration", init->name);
            return false;
        }
    }
    return true;
}

char* getStrFromValue(struct value_type* val) {
    if (val->type == NULL_TYPE || val->type == STRING_TYPE || val->type == OBJECT_TYPE) {
        return strdup((char*)val->data);
    } 
    if (val->type == INTEGER_TYPE) {
        char* res = calloc(16, sizeof(char));
        sprintf(res, "%d", *(int*)val->data);
        return res;
    }
    if (val->type == FLOAT_TYPE) {
        char* res = calloc(16, sizeof(char));
        sprintf(res, "%f", *(float*)val->data);
        return res;
    }
    if (val->type == BOOLEAN_TYPE) {
        char* res = calloc(8, sizeof(char));
        if (*(int*)val->data == 0) {
            strcat(res, "false");
        }
        else {
            strcat(res, "true");
        }
        return res;
    }
    return NULL;
}

bool doFunc(struct ast* ast, struct command_type* command) {
    struct func_call_type* call = (struct func_call_type*)command->command;
    char* name = call->name;
    if (!strcmp(name, "println!")) {
        char* tmp = calloc(256, sizeof(char));
        int size = 0;
        if (call->values->size == 0) {
            error("You are not allowed to not pass arguments to println!");
            return false;
        }
        if (call->values->values[0]->type != STRING_TYPE) {
            error("Invalid argument for func call %s", name);
            return false;
        }
        strcat(tmp, (char*)(call->values->values[0]->data));
        size += strlen((char*)(call->values->values[0]->data));
        char* tmpToFree = tmp;
        char* res = calloc(512, sizeof(char));
        char* placeholder_location = strstr(tmp, "{");
        int curIndex = 1;
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
            char* str;
            if (!strcmp(value, "")) {
                free(value);
                curIndex++;
                if (call->values->size < curIndex) {
                    error("Not enough values for println!");
                    return false;
                }
                struct value_type* val = call->values->values[curIndex - 1];
                if (val->type == FUNC_TYPE) {
                    struct command_type* com = (struct command_type*)val->data;
                    val = getDataFromFunc(ast, (struct func_call_type*)com->command);
                }
                if (!val) {
                    return false;
                }
                if (val->type == OBJECT_TYPE) {
                    struct member_type* mem = createMember(val, "");
                    val = getDataFromObject(ast, mem);
                    free(mem);
                }
                str = getStrFromValue(val);
                if (!str) {
                    return false;
                }
            }
            else {
                struct command_type* com = findValue(ast, value);
                bool isOp = false;
                for (int i = 0; i < strlen(value); ++i) {
                    if (value[i] == '+' || value[i] == '-' || value[i] == '*' || value[i] == '*') {
                        isOp = true;
                        break;
                    }
                }
                if (!com) {
                    if (!isOp) error("Undefined reference to %s", value);
                    return false;
                }
                struct member_type* mem = com->command;
                struct value_type* val = getValue(com);
                struct member_type* member = createMember(val, "");
                if (val->type == OBJECT_TYPE) {
                    val = getDataFromObject(ast, member);
                }
                else if (val->type == FUNC_TYPE) {
                    struct command_type* com = val->data;
                    struct func_call_type* call = com->command;
                    val = getDataFromFunc(ast, call);
                }
                if (val == NULL) {
                    return false;
                }
                free(member);
                str = getStrFromValue(val);
            }
            strcat(res, str);
            tmp += prefix_length + t;
            size -= prefix_length + t;
            free(str);
            placeholder_location = strstr(tmp, "{");
        }
        strncat(res, tmp, size);
        buffered_printf("%s\n", res);
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
        error("Implementation of funciton %s not found", name);
        return false;
    }
    struct ast* mergedAst = createAstToFunc(ast, impl->impl);
    if (impl->parametrs->size != call->values->size) {
        error("Incorrect number of arguments in function call %s, should be %d, but there is %d",
                impl->name, impl->parametrs->size, call->values->size);
        return false;
    }
    for (int i = 0; i < impl->parametrs->size; ++i) {
        struct value_type* val = call->values->values[i];
        if (val->type == OBJECT_TYPE) {
            struct command_type* com = findValue(ast, val->data);
            if (!com) {
                error("%s not found", val->data);
                return false;
            }
            val = getValue(com);
        }
        if (val->type != impl->parametrs->members[i]->value->type) {
            error("Incorrect type of parametr %s in function call %s, shoulde be %s, but there is %s",
                    impl->parametrs->members[i]->name, call->name, getStrFromValueType(impl->parametrs->members[i]->value->type),
                    getStrFromValueType(val->type));
            return false;
        }
        struct member_type* mem = createMember(val, impl->parametrs->members[i]->name);
        struct command_type* com = createCommand(0, MEMBER_COM_TYPE, (void*)mem);
        push_back_com(mergedAst->declarations, com);
    }

    for (int i = 0; i < impl->impl->functionCalls->size; ++i) {
        struct value_vec* newParametrs = createValueVec();
        struct func_call_type* c = impl->impl->functionCalls->commands[i]->command;
        for (int j = 0; j < c->values->size; ++j) {
            struct value_type* val = c->values->values[j];
            if (val->type != OBJECT_TYPE) {
                push_back_val(newParametrs, val);
            }
            else {
                for (int i = 0; i < mergedAst->declarations->size; ++i) {
                    struct member_type* mem = mergedAst->declarations->commands[i]->command;
                }
                struct command_type* com = findValue(mergedAst, (char*)val->data);
                if (!com) {
                    error("Not found value %s", val->data);
                    return false;
                }
                push_back_val(newParametrs, getValue(com));
            }
        }
        struct value_vec* tmp = c->values;
        c->values = newParametrs;
    }
    isInFunc = true;
    bool res = doAst(mergedAst);
    isInFunc = false;
    return res;
}

struct value_type* getValueFromIfCond(struct ast* ast, struct value_type* val) {
    if (val->type == OBJECT_TYPE) {
        struct command_type* com = findValue(ast, (char*)val->data);
        if (!com) {
            error("%s not found", val->data);
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
        error("This operation is not allowed with %s type", getStrFromValueType(leftVal->type));
        return -1;
    }
    if (!((rightVal->type == INTEGER_TYPE) || (rightVal->type == FLOAT_TYPE))) {
        error("This operation is not allowed with %s type", getStrFromValueType(rightVal->type));
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
        error("This operation is not allowed with %s type", getStrFromValueType(leftVal->type));
        return -1;
    }
    if (!((rightVal->type == INTEGER_TYPE) || (rightVal->type == FLOAT_TYPE))) {
        error("This operation is not allowed with %s type", getStrFromValueType(rightVal->type));
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
        error("Trying to check equality of %s and %s, which is not allowed\n", 
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
        error(": Left value in if cond not found");
        return false;
    }
    struct value_type* rightVal = getValueFromIfCond(ast, cond->rightVal);
    if (!rightVal) {
        error(": Right value in if cond not found");
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
        bool res = doAst(mergedAst);
        return res;
    default:
        return false;
    }
}

bool doCycle(struct ast* ast, struct command_type* com) {
    struct cycle_type* cycle = com->command;
    int parIndex = -1;
    if (cycle->par != NULL) {
        parIndex = ast->declarations->size;
        strcat(cycle->par->name, "+");
        struct command_type* com = createCommand(0, MEMBER_COM_TYPE, cycle->par);
        push_back_com(ast->declarations, com);
    }
    struct value_type* leftVal = getValueFromIfCond(ast, cycle->expr->leftVal);
    if (!leftVal) {
        error(": Left value in if cond not found");
        return false;
    }
    struct value_type* rightVal = getValueFromIfCond(ast, cycle->expr->rightVal);
    if (!rightVal) {
        error(": Right value in if cond not found");
        return false;
    }
    struct value_type* values[cycle->body->declarations->size];
    for (int i = 0; i < cycle->body->declarations->size; ++i) {
        struct member_type* mem = cycle->body->declarations->commands[i]->command;
        if (mem->value->type == OBJECT_TYPE) {
            values[i] = createValue(OBJECT_TYPE, strdup((char*)mem->value->data));
        } 
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
        for (int i = 0; i < cycle->body->declarations->size; ++i) {
            struct member_type* mem = cycle->body->declarations->commands[i]->command;
            if (values[i]->type == OBJECT_TYPE) {
                mem->value = createValue(OBJECT_TYPE, strdup((char*)values[i]->data));
            } 
        }
        res = checkExpression(leftVal, rightVal, cycle->expr->cmpChar);
    }
    if (parIndex >= 0) {
        struct member_type* mem = (struct member_type*)ast->declarations->commands[parIndex]->command;
        strcat(mem->name, "-");
    }
    return true;
}

int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // Для операндов или скобок
    }
}

// Функция для проверки, является ли символ частью операнда (переменной, функции и т.д.)
int isOperandChar(char c) {
    return isalnum(c) || c == '_' || c == '(' || c == ')';
}

// Функция для преобразования выражения в обратную польскую нотацию (ОПН)
char* infixToPostfix(const char* infix) {
    char* postfix = (char*)calloc(strlen(infix) * 3 + 1, sizeof(char));
    if (!postfix) {
        perror("Memory allocation failed");
        return NULL;
    }
    int index = 0;
    char stack[100];
    int top = -1;

    for (int i = 0; i < strlen(infix); i++) {
        if (isspace(infix[i])) continue; // Пропускаем пробелы
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            char op = infix[i];
            while (top >= 0 && getPrecedence(stack[top]) >= getPrecedence(op)) {
                postfix[index++] = stack[top--];
                postfix[index++] = ' ';
            }
            stack[++top] = op;
        }
        else {
            // Найден операнд
            int j = i;
            bool isBrackets = false;
            while (j != strlen(infix)) {
                if (!isBrackets && (infix[j] == '+' || infix[j] == '-' || infix[j] == '*' || infix[j] == '/')) break;
                if (infix[j] == '(') isBrackets = true;
                if (infix[j] == ')' && isBrackets) isBrackets = false;
                j++;
            }

            // Копируем операнд в postfix
            int operandLength = j - i;
            strncpy(postfix + index, infix + i, operandLength);
            index += operandLength;
            postfix[index++] = ' ';
            i = j - 1;
        }
    }

    while (top >= 0) {
        postfix[index++] = stack[top--];
        postfix[index++] = ' ';
    }

    postfix[index] = '\0'; // Завершаем строку

    return postfix;
}

struct value_type* getDataFromObject(struct ast* ast, struct member_type* mem) {
    char* data = mem->value->data;
    struct value_type* res = createValue(NULL_TYPE, NULL);
    char* leftVal = calloc(64, sizeof(char));
    char* rightVal = calloc(64, sizeof(char));
    char op = 0;
    bool isLeft = true;
    bool isInBrackets = false;
    char* postfix = infixToPostfix(data);
    char* strWSpase = calloc(strlen(data)+1, sizeof(char));
    strcat(strWSpase, data); strcat(strWSpase, " ");
    if (!strcmp(postfix, strWSpase)) {
        free(strWSpase);
        if (!fillData(ast, res, data, NULL, '+')) return NULL;
        return res;
    }
    free(strWSpase);
    if (!postfix) {
        return NULL;
    }
    char* stack[256];
    int stackSize = 0;
    char* oper = calloc(32, sizeof(char));
    int index = 0;
    bool isBrackets = false;
    char* bracketsValue = calloc(32, sizeof(char));
    for (int i = 0; i < strlen(postfix)-1; ++i) {
        if (postfix[i] == '(') isBrackets = true;
        if (postfix[i] == ' ') {
            if (bracketsValue[0] != 0) {
                struct value_type* val = getValueFromStr(bracketsValue);
                if (!val) {
                    return NULL;
                }
                if (val->type == OBJECT_TYPE) {
                    struct member_type* mem = createMember(val, "");
                    val = getDataFromObject(ast, mem);
                    free(mem);
                    if (!val) {
                        return NULL;
                    }
                }
                if (val->type == FUNC_TYPE) {
                    struct command_type* com = (struct command_type*)val->data;
                    struct func_call_type* call = (struct func_call_type*)com->command;
                    val = getDataFromFunc(ast, call);
                    if (!val) {
                        return NULL;
                    }
                }
                strcat(oper, "(");
                strcat(oper, getStrFromValue(val));
                strcat(oper, ")");
                free(bracketsValue);
                bracketsValue = calloc(32, sizeof(char));
            }
            if (oper[0] == 0) {
                continue;
            }
            stack[stackSize++] = strdup(oper);
            free(oper);
            oper = calloc(32, sizeof(char));
            index = 0;
            continue;
        }
        if (!isBrackets && (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')) {
            char* op = calloc(1, sizeof(char));
            op[0] = postfix[i];
            if (i == strlen(postfix)-2) {
                char* left = strdup(stack[stackSize-- -1]);
                free(stack[stackSize]);
                char* right = strdup(stack[stackSize-- -1]);
                free(stack[stackSize]);
                if (!fillData(ast, res, right, left, op[0])) {
                    return NULL;
                }
                free(oper);
                free(left);
                free(right);
                free(postfix);
                return res;
            }
            char* left = strdup(stack[stackSize-- -1]);
            free(stack[stackSize]);
            char* right = strdup(stack[stackSize-- -1]);
            free(stack[stackSize]);
            if (!fillData(ast, res, right, left, op[0])) {
                return NULL;
            }
            char* nowRes = getStrFromValue(res);
            stack[stackSize++] = strdup(nowRes);
            free(nowRes);
            free(op);
            free(left);
            free(right);
        }
        else {
            if (isBrackets) {
                if (postfix[i] != '(' && postfix[i] != ')') bracketsValue[strlen(bracketsValue)] = postfix[i];
            }
            else {
                oper[index++] = postfix[i];
            }
        }
        if (isBrackets && postfix[i] == ')') isBrackets = false;
    }
    free(postfix);
    return res;
}

bool doInit(struct ast* ast, struct command_type* command) {
    int num = command->num;
    struct member_type* mem = command->command;
    struct command_type* com = findValue(ast, mem->name);
    struct value_type* val = getValue(com);
    struct value_type* finalValue = mem->value;
    if (!com || num < com->num) {
        error("No such variable - %s in %d line", mem->name, num);
        return false;
    }
    if (mem->value->type == OBJECT_TYPE) {
        finalValue = getDataFromObject(ast, mem);
    }
    if (finalValue->type != val->type) {
        error("Incompletable types: trying to init %s to %s in %d line", getStrFromValueType(finalValue->type),
        getStrFromValueType(val->type), num);
        return false;
    }
    if (val->data != finalValue->data) {
        val->data = finalValue->data;
    }
    return true;
}

bool doCommand(struct ast* ast, struct command_type* com) {
    if (!com) {
        error("Command not found\n");
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
    case RETURN_TYPE:
        struct member_type* mem = (struct member_type*)com->command;
        returnValue = mem->value;
        return true;
    default:
        return true;
    }
}

bool doAst(struct ast* ast) { // void
    struct value_type* startValue = returnValue;
    if (!checkAst(ast)) {
        return false;
    }
    struct command_vec* vec = sortAst(ast);
    for (int i = 0; i < vec->size; ++i) {
        if(!doCommand(ast, vec->commands[i])) {
            return false;
        }
        if (isInFunc) {
            if (returnValue != startValue) {
                return true;
            }
        }
    }
    return true;
}

bool doAllAst(struct ast* ast) {
    for (int i = 0; i < ast->functionCalls->size; ++i) {
        struct func_call_type* c = ast->functionCalls->commands[i]->command;
        if (!strcmp(c->name, "main")) {
            error("You are not allowed to call main");
            return false;
        }
    } 
    push_back_com(ast->functionCalls, createCommand(getMaxNum(ast)+1, FUNC_CALL_TYPE, createFuncCall(strdup("main"), createValueVec())));
    int res = doAst(ast);
    for (int i = 0; i < g_astContSize; ++i) {
        freeAstWithoutData(g_astCont[i]);
    }
    for (int i = 0; i < g_astContSize; ++i) {
        if (!g_astCont[i]) continue;
        if (!g_astCont[i]->declarations || !g_astCont[i]->initializations || !g_astCont[i]->cycles || !g_astCont[i]->functionCalls || !g_astCont[i]->functions 
            || !g_astCont[i]->if_expressions) continue;;
        free(g_astCont[i]);
    }
    for (int i = 0; i < g_vecContSize; ++i) {
        if (g_vecCont[i]->commands) {
            free(g_vecCont[i]->commands);
        }
        free(g_vecCont[i]);
    } 
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

struct ast* mergeAst(struct ast* first, struct ast* second) {
    struct ast* ast = createAst();
    g_astCont[g_astContSize++] = ast;
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
        push_back_com(ast->declarations, source->declarations->commands[i]);
    }
    return ast;
}

struct ast* createAstToDoWOVal(struct ast* source, struct ast* toDo, int n) {
    struct ast* ast = createAst();
    g_astCont[g_astContSize++] = ast;

    for (int i = 0; i < toDo->declarations->size; ++i) {
        push_back_com(ast->declarations, toDo->declarations->commands[i]);
    }
    for (int i = 0; i < toDo->initializations->size; ++i) {
        push_back_com(ast->initializations, toDo->initializations->commands[i]);
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
 
struct ast* createAstToFunc(struct ast* source, struct ast* toDo) {
    struct ast* ast = createAst();
    g_astCont[g_astContSize++] = ast;

    for (int i = 0; i < toDo->declarations->size; ++i) {
        push_back_com(ast->declarations, toDo->declarations->commands[i]);
    }
    for (int i = 0; i < toDo->initializations->size; ++i) {
        push_back_com(ast->initializations, toDo->initializations->commands[i]);
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

void free_command_vec(struct command_vec* vec) {
    if (vec) {
        if (vec->commands) {
            for (size_t i = 0; i < vec->size; ++i) {
                if (vec->commands[i]) {
                    switch (vec->commands[i]->type) {
                        case MEMBER_COM_TYPE: 
                            if (vec->commands[i]->command) {
                                struct value_type* val = (struct value_type*)vec->commands[i]->command;
                                if(val->data){
                                    free(val->data);
                                    val->data = NULL;
                                }
                                free(val);
                                val = NULL;
                            }
                            break;
                        case INIT_COM_TYPE: 
                            if (vec->commands[i]->command) {
                                struct value_type* val = (struct value_type*)vec->commands[i]->command;
                                if(val->data){
                                    free(val->data);
                                }
                                free(val);
                                vec->size = 0;
                            }
                            break;
                        case FUNC_CALL_TYPE: 
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
                        case FUNC_IMPL_TYPE:
                        // Очистим позже 
                            break;
                        case IF_COM_TYPE: 
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
                         case CYCLE_COM_TYPE: 
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
            vec->commands = NULL;
        }
        free(vec);
        vec = NULL;
    }
}

void freeAstWithoutData(struct ast* ast) {
    if (!ast->declarations || !ast->initializations || !ast->cycles || !ast->functionCalls || !ast->functions 
        || !ast->if_expressions) {
        free(ast);
        return;
    }
    free(ast->declarations->commands);
    ast->declarations->commands = NULL;
    free(ast->declarations);
    ast->declarations = NULL;
    free(ast->initializations->commands);
    ast->initializations->commands = NULL;
    free(ast->initializations);
    ast->initializations = NULL;
    free(ast->functionCalls->commands);
    ast->functionCalls->commands = NULL;
    free(ast->functionCalls);
    ast->functionCalls = NULL;
    free(ast->functions->commands);
    ast->functions->commands = NULL;
    free(ast->functions);
    ast->functions = NULL;
    free(ast->if_expressions->commands);
    ast->if_expressions->commands = NULL;
    free(ast->if_expressions);
    ast->if_expressions= NULL;
    free(ast->cycles->commands);
    ast->cycles->commands = NULL;
    free(ast->cycles);
    ast->cycles = NULL;
    
    
    return;
}

void freeAst(struct ast* ast) {
    if (ast) {
        if (ast->returnValue) {
            if (ast->returnValue->data) {
                free(ast->returnValue->data);
                ast->returnValue->data = NULL;
            }
            free(ast->returnValue);
            ast->returnValue = NULL;
        }
        if (ast->declarations) {
            free_command_vec(ast->declarations);
        }
        if (ast->initializations) {
            free_command_vec(ast->initializations);
        }
        if (ast->functionCalls) {
            free_command_vec(ast->functionCalls);
        }
        if (ast->functions) {
            struct command_vec* func_command_vec = ast->functions;
            if (func_command_vec && func_command_vec->commands) {
                for (size_t i = 0; i < func_command_vec->size; i++) {
                    if (func_command_vec->commands[i]) {
                        struct func_impl_type* func_impl = (struct func_impl_type*)func_command_vec->commands[i]->command;
                        if (!func_impl) free_func_impl(func_impl);
                        free(func_command_vec->commands[i]);
                    }
                }
                free(func_command_vec->commands);
            }
            free(func_command_vec);
        }
        if (ast->if_expressions) {
            free_command_vec(ast->if_expressions);
        }
        if (ast->cycles) {
            free_command_vec(ast->cycles);
        }
    }
}

void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
  
    fprintf(stdout, "Error: ");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
  
    va_end(args);

    freeAst(globalAst);
  
    exit(EXIT_FAILURE);
  }