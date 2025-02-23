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
        res = yyparse();
        if (res == 0) {
            printf("ok\n");
            return 0;
        }
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        return 1;
    }

    yyin = inputFile;
    res = yyparse();

    fclose(inputFile);
    if (res == 0) {
        printf("ok\n");
        return 0;
    }
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