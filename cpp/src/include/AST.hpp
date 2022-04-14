#ifndef AST_HPP
#define AST_HPP

#include <cstdlib>

struct AST_T {
    enum type {
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
    };
    int type;

    // AST_VARIABLE_DEFINITION
    char* variable_definition_variable_name;
    AST_T* variable_definition_value;

    // AST_VARIABLE
    char* variable_name;

    // AST_FUNCTION_CALL
    char* function_call_name;
    AST_T** function_call_arguments;
    size_t function_call_arguments_size;

    // AST_STRING
    char* string_value;

    // AST_COMPOUND;
    AST_T** compound_value;
    size_t compound_size;
};

AST_T* ast_init(int type){
    AST_T* ast = (AST_T*)calloc(1, sizeof(AST_T));
    ast->type = type;
    ast->variable_definition_variable_name = nullptr;
    ast->variable_definition_value = nullptr;
    ast->variable_name = nullptr;
    ast->function_call_name = nullptr;
    ast->function_call_arguments = nullptr;
    ast->function_call_arguments_size = 0;
    ast->string_value = nullptr;
    ast->compound_value = nullptr;
    ast->compound_size = 0;
    return ast;
};

#endif