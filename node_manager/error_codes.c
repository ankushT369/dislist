#include "error_codes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void handle_response_code(int error_code, char* buffer) {
    switch (error_code) {
        case SUCCESS:
            strcpy(buffer, "Success: The operation was completed successfully.");
            break;
        case INVALID_SYNTAX_COMMAND_TRAVERSE:
            strcpy(buffer, "Error: Invalid Syntax for TRAVERSE. Usage: TRAVERSE");
            break;
        case INVALID_SYNTAX_COMMAND_INSERT:
            strcpy(buffer, "Error: Invalid Syntax for INSERT. Usage: INSERT <number>");
            break;
        case INVALID_SYNTAX_COMMAND_REMOVE:
            strcpy(buffer, "Error: Invalid Syntax for REMOVE. Usage: REMOVE");
            break;
        case UNKNOWN_COMMAND:
            strcpy(buffer, "Error: Unknown Command. Available Commands: TRAVERSE, INSERT <number>, REMOVE");
            break;
        case OUT_OF_RANGE:
            strcpy(buffer, "Error: Out of Range - The specified operation exceeds allowed limits.");
            break;
        case FAILURE:
            strcpy(buffer, "Error: The operation failed.");
            break;
        default:
            sprintf(buffer, "Error: Unrecognized Error Code %d.\n", error_code);
            break;
    }
}
