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
            printf("Error: Invalid Syntax for TRAVERSE.\n");
            printf("Usage: TRAVERSE\n");
            break;
        case INVALID_SYNTAX_COMMAND_INSERT:
            printf("Error: Invalid Syntax for INSERT.\n");
            printf("Usage: INSERT <number>\n");
            break;
        case INVALID_SYNTAX_COMMAND_REMOVE:
            printf("Error: Invalid Syntax for REMOVE.\n");
            printf("Usage: REMOVE\n");
            break;
        case UNKNOWN_COMMAND:
            printf("Error: Unknown Command.\n");
            printf("Available Commands: TRAVERSE, INSERT <number>, REMOVE\n");
            break;
        case OUT_OF_RANGE:
            printf("Error: Out of Range - The specified operation exceeds allowed limits.\n");
            break;
        case FAILURE:
            printf("Error: The operation failed.\n");
            break;
        case INTERNAL_ERROR:
            printf("Error: Internal Server Error.\n");
            break;
        default:
            printf("Error: Unrecognized Error Code %d.\n", error_code);
            break;
    }
}
