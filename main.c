#include <stdio.h>
#include "sent.tab.h"
#include "ast.h"
#include <string.h>
#include "astHelper.h"

extern FILE *yyin;
extern int yyparse();
extern char* output_buffer;


struct ast* globalAst;
struct ast* g_astCont[2048];
int g_astContSize = 0;

int main(int argc, char **argv) {
    int res;
    globalAst = createAst();
    if (argc != 2) {
        printf("No file\n");
        char* str = strdup("test.txt");
        FILE *inputFile = fopen(str, "r");
        
        yyin = inputFile;
        res = yyparse();
        fclose(inputFile);
    }
    else {
        FILE *inputFile = fopen(argv[1], "r");
        if (!inputFile) {
            return 1;
        }

        yyin = inputFile;
        res = yyparse();

        fclose(inputFile);
    }
    if (res != 0) {
        printf("Error in %d\n", 0);
        return 1;
    } 
    if (!doAllAst(globalAst)) {
        printf("\n");
    }
    else {
        flush_buffer();
    }
    freeAst(globalAst);
    return 0;
}