#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "lexer.hpp"

struct PARSER_T {
    LEXER_T* lexer;
    TOKEN_T* current_token;
};

PARSER_T* parser_init(LEXER_T* lexer){

}

void parser_eat(PARSER_T* parser, int token_type){
     
}

AST_T* parser_parse(PARSER_T* parser){
    
}

#endif