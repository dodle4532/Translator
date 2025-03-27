#include <stdio.h>
#include "sent.tab.h"
#include "ast.h"
#include <string.h>
#include "astHelper.h"

extern FILE *yyin;
extern int yyparse();


struct ast* ast;

int main(int argc, char **argv) {
    int res;
    ast = createAst();
    if (argc != 2) {
        printf("No file\n");
        char* str = strdup("1.txt");
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
    // struct member_type* mem = (struct member_type*)ast->declarations->commands[1]->command;
    // printf("%d %d\n", ast->declarations->commands[1]->num, ast->cycles->commands[1]->num);
    // printf("%s - %d\n", mem->name, *(int*)mem->value->data);
    // struct func_call_type* f = (struct func_call_type*)ast->functionCalls->commands[0]->command;
    // printf("%s - %d %d %d\n", f->name, *(int*)f->values->values[0]->data, *(int*)f->values->values[1]->data, *(int*)f->values->values[2]->data);
    // struct func_call_type* f1 = (struct func_call_type*)ast->functionCalls->commands[1]->command;
    // printf("%s - %s\n", f1->name, (char*)f1->values->values[0]->data);
    // struct func_impl_type* f2 = (struct func_impl_type*)ast->functions->commands[0]->command;
    // struct func_call_type* f3 = (struct func_call_type*)f2->impl->functionCalls->commands[0]->command;
    // printf("%s - %s (%s(%s)), return %s\n", f2->name, f2->parametrs->members[0]->name, (char*)f3->name,
    //  (char*)f3->values->values[0]->data, f2->returnValue->data);
    // struct if_expr_type* f4 = (struct if_expr_type*)ast->if_expressions->commands[0]->command;
    // struct func_call_type* f5 = (struct func_call_type*)f4->body->functionCalls->commands[0]->command;
    // printf("%s %s %d : %s\n", f4->cond->leftVal->data, f4->cond->cmpChar, *(int*)f4->cond->rightVal->data, f5->name);
    // struct cycle_type* f6 = (struct cycle_type*)ast->cycles->commands[0]->command;
    // struct member_type* f7 = (struct member_type*)f6->body->initializations->commands[0]->command;
    // printf("%s %s %d {%s = %d}\n", f6->expr->leftVal->data, f6->expr->cmpChar, *(int*)f6->expr->rightVal->data, f7->name, *(int*)f7->value->data);

    // for (int i = 0; i < ast->declarations->size; ++i) {
    //     struct member_type* mem = ast->declarations->commands[i]->command;
    //     printf("%s\n", mem->name);
    // }
    if (!doAllAst(ast)) {
        printf("\n");
    }
    // for (int i = 0; i < ast->declarations->size; ++i) {
    //     struct member_type* mem = ast->declarations->commands[i]->command;
    //     printf("%s\n", mem->name);
    // }
    // struct command_vec* sorted = sortAst(ast);
    freeAst(ast);
    return 0;
}