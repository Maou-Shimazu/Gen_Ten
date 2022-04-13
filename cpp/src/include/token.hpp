#ifndef TOKEN_H
#define TOKEN_H

#include <cstdlib>

struct TOKEN_T {
    enum{
        TOKEN_IDENTIFIER, // Identifiers
        TOKEN_EQUALS, // equal sign token
        TOKEN_STRING, // string token
        TOKEN_SEMI, // semicolon token
        TOKEN_COLON, // colon token
        TOKEN_LPAREN, // left parenthesis token
        TOKEN_RPAREN,   // right parenthesis token
        TOKEN_INTEGER, // integer token
        TOKEN_EOF, // end of file token
        TOKEN_OPERATOR, // operator token
        TOKEN_KEYWORD, // keyword token
        TOKEN_SEPARATOR, // separator token
        TOKEN_COMMENT, // comment token
        TOKEN_ERROR // error token
    };
    char* value; // value of the token
    int type; // type of the token
};

// Token init, takes type of character being parsed and the value of that character and returns a token
TOKEN_T* token_init(int type, char* value){
    TOKEN_T* token  = (TOKEN_T*)calloc(1, sizeof(TOKEN_T)); // allocate memory for the token, size of struct
    token->type = type; // set type 
    token->value = value; // set value
    return token;
};

#endif