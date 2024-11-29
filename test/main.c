#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Error Codes
#define SUCCESS 200
#define INVALID_SYNTAX_COMMAND_TRAVERSE 1001
#define INVALID_SYNTAX_COMMAND_INSERT 1002
#define INVALID_SYNTAX_COMMAND_REMOVE 1003
#define UNKNOWN_COMMAND 101
#define OUT_OF_RANGE 102
#define FAILURE 404
#define INTERNAL_ERROR 301

// Function to handle server responses
void handle_response(const char *response) {
    int error_code;
    char error_message[256];

    // Parse the response (assuming the format is "<ERROR_CODE>;<ERROR_MESSAGE>")
    sscanf(response, "%d;%255[^\n]", &error_code, error_message);

    // Handle based on error code
    switch (error_code) {
        case SUCCESS:
            printf("Success: %s\n", error_message);
            break;
        case INVALID_SYNTAX_COMMAND_TRAVERSE:
            printf("Error: Invalid Syntax for TRAVERSE - %s\n", error_message);
            break;
        case INVALID_SYNTAX_COMMAND_INSERT:
            printf("Error: Invalid Syntax for INSERT - %s\n", error_message);
            break;
        case INVALID_SYNTAX_COMMAND_REMOVE:
            printf("Error: Invalid Syntax for REMOVE - %s\n", error_message);
            break;
        case UNKNOWN_COMMAND:
            printf("Error: Unknown Command - %s\n", error_message);
            break;
        case OUT_OF_RANGE:
            printf("Error: Out of Range - %s\n", error_message);
            break;
        case FAILURE:
            printf("Error: Operation Failed - %s\n", error_message);
            break;
        case INTERNAL_ERROR:
            printf("Error: Internal Server Error - %s\n", error_message);
            break;
        default:
            printf("Error: Unrecognized Error Code %d - %s\n", error_code, error_message);
            break;
    }
}

// Helper function to simulate command validation and send responses
void validate_and_handle_command(const char *command) {
    char response[512];

    if (strncmp(command, "TRAVERSE", 8) == 0) {
        if (strlen(command) > 8) {
            // Invalid TRAVERSE syntax
            snprintf(response, sizeof(response), "%d;Extra arguments in TRAVERSE command", INVALID_SYNTAX_COMMAND_TRAVERSE);
        } else {
            // Success for TRAVERSE
            snprintf(response, sizeof(response), "%d;TRAVERSE executed successfully", SUCCESS);
        }
    } else if (strncmp(command, "INSERT", 6) == 0) {
        int value;
        if (sscanf(command, "INSERT %d", &value) != 1) {
            // Invalid INSERT syntax
            snprintf(response, sizeof(response), "%d;Invalid or missing number for INSERT command", INVALID_SYNTAX_COMMAND_INSERT);
        } else {
            // Success for INSERT
            snprintf(response, sizeof(response), "%d;Value %d inserted successfully", SUCCESS, value);
        }
    } else if (strncmp(command, "REMOVE", 6) == 0) {
        if (strlen(command) > 6) {
            // Invalid REMOVE syntax
            snprintf(response, sizeof(response), "%d;Extra arguments in REMOVE command", INVALID_SYNTAX_COMMAND_REMOVE);
        } else {
            // Success for REMOVE
            snprintf(response, sizeof(response), "%d;REMOVE executed successfully", SUCCESS);
        }
    } else {
        // Unknown command
        snprintf(response, sizeof(response), "%d;Unknown command received", UNKNOWN_COMMAND);
    }

    // Handle the generated response
    handle_response(response);
}

// Main function for testing
int main() {
    // Test cases
    validate_and_handle_command("TRAVERSE");
    validate_and_handle_command("TRAVERSE extra");
    validate_and_handle_command("INSERT");
    validate_and_handle_command("INSERT 42");
    validate_and_handle_command("REMOVE");
    validate_and_handle_command("REMOVE extra");
    validate_and_handle_command("INVALID_COMMAND");

    return 0;
}

