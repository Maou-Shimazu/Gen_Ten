#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include "AST.hpp"
#include "lexer.hpp"

struct PARSER_T {
    LEXER_T* lexer;
    TOKEN_T* current_token;
};

PARSER_T* parser_init(LEXER_T* lexer){
    PARSER_T* parser = (PARSER_T*)calloc(1, sizeof(PARSER_T));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    return parser;
}

void parser_eat(PARSER_T* parser, int token_type){
     if(parser->current_token->type == token_type)
         parser->current_token = lexer_get_next_token(parser->lexer);
     else std::cout << "Unexpexted token: " 
                    << parser->current_token->value << ", with type: " 
                    << parser->current_token->type << std::endl;
}

AST_T* parser_parse_statement(PARSER_T* parser){
    switch (parser->current_token->type) {
        case TOKEN_IDENTIFIER: return parser_parse_identifier(parser); 
        
    }
}

AST_T* parser_parse_statements(PARSER_T* parser){
    AST_T* compound = ast_init(AST_COMPOUND);
    compound->compound_value = (AST_T**)calloc(1, sizeof(AST_T*));
    AST_T* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;

    while(parser->current_token->type == TOKEN_T::TOKEN_SEMI){
        parser_eat(parser, TOKEN_T::TOKEN_SEMI);

        AST_T* ast_statement = parser_parse_statement(parser);
        compound->compound_size+=1;

        compound->compound_value = (AST_T**)realloc(compound->compound_value, 
        compound->compound_size * sizeof(AST_T*));

        compound->compound_value[compound->compound_size-1] = ast_statement;
    }

    return compound;
}

AST_T* parser_parse(PARSER_T* parser){
    return parser_parse_statements(parser);
}

AST_T* parser_parse_expr(PARSER_T* parser){
    switch(parser->current_token->type) {
        case TOKEN_STRING: return parser_parse_string(parser); 
    }
}

AST_T* parser_parse_factor(PARSER_T* parser){

}

AST_T* parser_parse_term(PARSER_T* parser){

}

AST_T* parser_parse_function_call(PARSER_T* parser){

}

AST_T* parser_parse_variable(PARSER_T* parser){
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_IDENTIFIER); // var name or function call name 
    if (parser->current_token->type = TOKEN_LPAREN)
        return parser_parse_function_call(parser);

    AST_T* ast_variable = ast_init(AST_VARIABLE);
    ast_variable->variable_name = token_value;

    return ast_variable;

}

AST_T* parser_parse_string(PARSER_T* parser){
    AST_T* ast_string = ast_init(AST_STRING);
    ast_string->string_value = parser->current_token->value;

    parser_eat(parser, TOKEN_STRING);

    return ast_string;
}

AST_T* parser_parse_identifier(PARSER_T* parser) {
    if (strcmp(parser->current_token->value, "var") == 0) {
        return parser_parse_variable_definition(parser);
    } else {
        return parser_parse_variable(parser);
    }
}

AST_T* parser_parse_variable_definition(PARSER_T* parser) [
    parser_eat(parser, TOKEN_IDENTIFIER); //var
    char* variable_definition_variable_name = parser->current_token->value; 
    parser_eat(parser, TOKEN_IDENTIFIER);
    parser_eat(parser, TOKEN_EQUALS);
    AST_T* variable_definition_value = parser_parse_expr(parser);

    AST_T* variable_definition = ast_init(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_variable_name = variable_definition_variable_name;
    variable_definition->variable_definition_value = variable_definition_value;

    return variable_definition;
]

#endif