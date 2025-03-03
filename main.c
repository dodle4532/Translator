#include <stdio.h>
#include "sent.tab.h" // Подключаем заголовочный файл, сгенерированный Bison
#include "ast.h"

extern FILE *yyin; // Объявляем yyin
extern int yyparse();

struct ast* ast;

int main(int argc, char **argv) {
    int res;
    ast = createAst();
    if (argc != 2) {
        printf("No file\n");
        // res = yyparse();
        // if (res == 0) {
        //     printf("ok\n");
        // }
        // else {
        //     return 1;
        // }
        return 1;
    }
    else {
        FILE *inputFile = fopen(argv[1], "r");
        if (!inputFile) {
            return 1;
        }

        yyin = inputFile;
        res = yyparse();

        fclose(inputFile);
        if (res == 0) {
            printf("ok\n");
        }
        else {
            return 1;
        }
    }
    struct member_type* mem = (struct member_type*)ast->declarations->commands[0]->command;
    printf("%d %d\n", ast->declarations->commands[0]->num, ast->functionCalls->commands[0]->num);
    printf("%s - %d\n", mem->name, *(int*)mem->value->data);
    struct func_call_type* f = (struct func_call_type*)ast->functionCalls->commands[0]->command;
    printf("%s - %d %d %d\n", f->name, *(int*)f->values->values[0]->data, *(int*)f->values->values[1]->data, *(int*)f->values->values[2]->data);
    struct func_call_type* f1 = (struct func_call_type*)ast->functionCalls->commands[1]->command;
    printf("%s - %s\n", f1->name, (char*)f1->values->values[0]->data);
    struct func_impl_type* f2 = (struct func_impl_type*)ast->functions->functions[0];
    struct func_call_type* f3 = (struct func_call_type*)f2->astWOfuncImpl->functionCalls->commands[0]->command;
    printf("%s - %s (%s(%s))\n", f2->name, f2->parametrs->members[0]->name, (char*)f3->name, (char*)f3->values->values[0]->data);
    return 0;
}
// int main(int argc, char **argv) {
//     FILE *inputFile;
  
//     if (argc != 2) {
//       //perror("Incorrect number of arguments\n");
//       return yyparse();
//     }
  
//     inputFile = fopen(argv[1], "r"); // Открываем файл на чтение
//     if (!inputFile) {
//       perror("Error opening file");
//       return 1; // Возвращаем код ошибки
//     }
  
//     yyin = inputFile;   // Перенаправляем ввод на файл
//     yyparse();
  
//     fclose(inputFile);
//     return yyparse();
//   }
  
//   void yyerror(char *s) {
//     fprintf(stderr, "error: %s\n", s);
//   }