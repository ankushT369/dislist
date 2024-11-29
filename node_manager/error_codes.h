#ifndef ERROR_CODES_H
#define ERROR_CODES_H


typedef enum {
    SUCCESS = 200,
    INVALID_SYNTAX_COMMAND_TRAVERSE = 111,
    INVALID_SYNTAX_COMMAND_INSERT = 112,
    INVALID_SYNTAX_COMMAND_REMOVE = 113,
    UNKNOWN_COMMAND = 101,
    OUT_OF_RANGE = 102,
    FAILURE = 404
} Status;

void handle_response_code(int, char*);

#endif // ERROR_CODES_H
