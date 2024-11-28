#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[100];
    while (1) {
        // Clear the screen
        system("clear"); // For Linux/Mac. Use system("cls"); on Windows.

        // Show the output
        printf("Displaying value: %s\n", input);

        // Ask for input on another line
        printf("Enter a value (type 'exit' to quit): ");
        fgets(input, 100, stdin);

        // Remove trailing newline
        if (input[0] != '\0' && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // Break if user types "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }
    }
    return 0;
}

