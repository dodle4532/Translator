struct command_vec* sortAst(struct ast* ast); // Сортировка ast в порядке номеров команд
struct command_type* findValue(struct ast* ast, char* name); // Поиск значения по имене
struct value_type* getValue(struct command_type* com); // Получение value из комманды типа MEMBER_COM_TYPE
struct value_type* getValueFromStr(char* str); // Получение value из строки
int getIntRes(int l, int r, char op); // Совершнение опарции над int
float getFloatRes(float l, float r, char op); // Совершнение опарции над float
struct value_type* getOp(struct value_type* left, struct value_type* right, char op); // Совершение операции над value
char* getStrFromValue(struct value_type* val); // Получение строки из value
const char* getStrFromValueType(enum VALUE_TYPE type); // Получени строки из типа данных (для вывода на экран)
struct value_type* getDataFromObject(struct ast* ast, struct member_type* mem); // Получение value из value типа Object (поиск значения) и совершение операции в случае, если необходимо
struct value_type* getDataFromFunc(struct ast* ast, struct func_call_type* call); // Получение value из func_call
bool checkAst(struct ast* ast); // Проверка ast (Проверка, что нет переопределения значений, проверка, что для всех инициализаций есть определения переменных выше)
bool doFunc(struct ast* ast, struct command_type* command); // Выполнение функции
bool doIf(struct ast* ast, struct command_type* com); // Выполнения if
bool doCycle(struct ast* ast, struct command_type* com); // Выполнение цикла
int checkExpression(struct value_type* leftVal, struct value_type* rightVal, char* cmpChar); // Проверка условия
bool checkEquality(struct value_type* leftVal, struct value_type* rightVal); // Проверка равенства
int checkMore(struct value_type* leftVal, struct value_type* rightVal); // Проверка больше
int checkLess(struct value_type* leftVal, struct value_type* rightVal); // Проверка меньше
struct ast* mergeAst(struct ast* first, struct ast* second); // Слияние ast
struct ast* createAstToDoWVal(struct ast* source, struct ast* toDo, int n); // Создание ast с передачей переменных
struct ast* createAstToDoWOVal(struct ast* source, struct ast* toDo, int n); // Создание ast без передачи переменных
struct ast* createAstToFunc(struct ast* source, struct ast* toDo); // Создание ast для функции
bool doAst(struct ast* ast); // Выполнение ast
bool doAllAst(struct ast* ast); // Выполнение изначального ast
int getMaxNum(struct ast* ast); // Получение максимального номера команды в ast

void freeAst(struct ast* ast); // Освобождение ast
void freeAstWithoutData(struct ast* ast); // Освобождение оболочки ast (без данных внутри)
void free_value_vec(struct value_vec* vec); // Освобождение value_vec
void free_member_vec(struct member_vec* vec); // Освобождение member_vec
void free_func_impl(struct func_impl_type* func_impl); // Освобождение func_impl
void free_command_vec(struct command_vec* vec); // Освобождение command_vec

void buffered_printf(const char *format, ...); // Функция для записи в буфер
void flush_buffer(); // Функция для вывода содержимого буфера на экран
void error(const char *format, ...); // Вывод ошибки на экран