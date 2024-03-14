#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "include/lexer.hpp"
#include "include/parser.hpp"

int main(int argc, char **argv){
    char text[] = "xp text = \"MXP\"; \n xp anotherTest = \"more MXP\"; ";
    LEXER_T* lexer = lexer_init(text);

    PARSER_T* parser = parser_init(lexer);
    AST_T* root = parser_parse(parser);

    std::cout << root->type;
    return 0;
}