#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "include/lexer.hpp"

int main(int argc, char **argv){
    char text[] = "xp text = \"MXP\"; \n xp anotherTest = \"more MXP\"; ";
    LEXER_T* lexer = lexer_init(text);

    TOKEN_T* token = nullptr;
    while ((token = lexer_get_next_token(lexer)) != nullptr){
        std::cout << "TOKEN(" << token->type << " , " << token->value << ")" << std::endl;
    }
    free(token);
    return 0;
}