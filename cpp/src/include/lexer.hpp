#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <cstdlib>
#include <iostream>

struct LEXER_T {
    char* text_contents; // contents of the text
    char current_char; // current character being processed
    unsigned int index; // index of the current character being processed
};
//--- Lexer type definitions ---//
// Lexer initialization, takes text contents that needs to be parsed. returns the lexer pointer
LEXER_T* lexer_init(char* text_contents){
    LEXER_T* lexer = (LEXER_T*)calloc(1, sizeof(LEXER_T)); // allocate the size of Lexer_T class to a pointer of type lexer.
    lexer->text_contents = text_contents; // set text contents
    lexer->index = 0; // set index to zero
    lexer->current_char = text_contents[lexer->index]; // set current character to the first character in the text
    return lexer;
};


//--- Lexer functions ---//

void lexer_advance(LEXER_T* lexer){
    if(lexer->current_char != '\0' && lexer->index < strlen(lexer->text_contents)){ // if the current character is not null and the index is less than the length of the text's contents
        lexer->index++; // increment the index
        lexer->current_char = lexer->text_contents[lexer->index]; // set the current character to the next character in the text
    }
};

void lexer_skip_whitespace(LEXER_T* lexer){
    while(lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n' || lexer->current_char == '\r'){ // while the current character is equal to any terminating or space characters, advance the lexer.
        lexer_advance(lexer);
    }
};
char* lexer_get_current_char_as_string(LEXER_T* lexer){
    char* current_char_as_string = (char*)calloc(2, sizeof(char)); // allocate size of char
    current_char_as_string[0] = lexer->current_char; //append the current character to the array.
    current_char_as_string[1] = '\0'; // add terminating object to end of array
    return current_char_as_string; //return the array pointer
};

//--- Token type definitions ---//

TOKEN_T* lexer_advance_with_token(LEXER_T* lexer, TOKEN_T* token){
    lexer_advance(lexer); // advance lexer and return token
    return token;
};

TOKEN_T* lexer_collect_string(LEXER_T* lexer){
    lexer_advance(lexer); // advance lexer

    char* value = (char*)calloc(1, sizeof(char)); // allocate size of char to value
    value[0] = '\0'; // terminating character at the entry point of value

    while (lexer->current_char != '"'){
        char* string = lexer_get_current_char_as_string(lexer); // get the array of the current characters aka as a string
        value = (char*)realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char)); // reallocate to value, the length of value plus the length of the string plus 1 times the size of character
        strcat(value, string); // concatenate value and string
        lexer_advance(lexer); // advance the lexer twice more
    }

    lexer_advance(lexer);
    return token_init(TOKEN_T::TOKEN_STRING, value); // return the token string 
}

TOKEN_T* lexer_collect_id(LEXER_T* lexer){

    char* value = (char*)calloc(1, sizeof(char)); // allocate size of char and initialize to termiating character
    value[0] = '\0';

    while (isalnum(lexer->current_char)){ // while the current character is alphanumeric
        char* string = lexer_get_current_char_as_string(lexer); // get the characters as a string
        value = (char*)realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char)); // reallocate value
        strcat(value, string); // concat
        lexer_advance(lexer); // advance
    }
    lexer_advance(lexer);
    return token_init(TOKEN_T::TOKEN_IDENTIFIER, value); // return the token identifier
}

TOKEN_T* lexer_get_next_token(LEXER_T* lexer){

    while(lexer->current_char != '\0' && lexer->index < strlen(lexer->text_contents)){

        if(lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n' || lexer->current_char == '\r')
            lexer_skip_whitespace(lexer);
         
        if(isalnum(lexer->current_char))
            return lexer_collect_id(lexer);

        if(lexer->current_char == '"')
            return lexer_collect_string(lexer);
        

        switch(lexer->current_char){
            case '\0': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_EOF, lexer_get_current_char_as_string(lexer))); break;
            case '=': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))); break;
            case ';': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); break;
            case ':': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_COLON, lexer_get_current_char_as_string(lexer))); break;
            case '(': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
            case ')': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
            case '+': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_OPERATOR, lexer_get_current_char_as_string(lexer))); break;
            case '-': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_OPERATOR, lexer_get_current_char_as_string(lexer))); break;
            case '*': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_OPERATOR, lexer_get_current_char_as_string(lexer))); break;
            case '/': return lexer_advance_with_token(lexer, token_init(TOKEN_T::TOKEN_OPERATOR, lexer_get_current_char_as_string(lexer))); break;
        }
    }
    return nullptr;
};


#endif // LEXER_H