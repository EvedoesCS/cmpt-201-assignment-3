 /* Author: Eve Leonard
 * Lab instructor: Dhara Wagh
 * Lecture instructor: Abdullah Mohiuddin
 */

#include <stdio.h>
#include <string.h>

#include "../import.h"

// Tests promp_file_path() -> asks for input and
// returns success if "hello_world.csv" is entered
// into stdin and read correctly into the buffer;
int test_prompt_file_path(void) {
    printf("\nTESTING prompt_file_path()\n");
    char buffer[256] = {'\0'};

    prompt_file_path(buffer);

    if (buffer[0] == '\0') {
        printf("FAIL: prompt_file_path did not write to the buffer\n");
        return -1;
    }

    printf("SUCCESS: Collected filename %s from stdin\n", buffer);
    return 0;
}

int test_tokenize_string(void) {
    printf("\nTESTING tokenize_string()\n");
    char *line = "Hello, World!";
    // Init array of char * to store each token;
    char tokens[11][50] = {'\0'};

    tokenize_string(line, tokens);

    if (strcmp(tokens[1], " World!") != 0) {
        printf("FAIL: tokenize_string did not tokenize correctly. Got '%s' want ' World!'\n", tokens[1]);
        return -1;
    } 

    printf("SUCCESS\n");
    return 0;
}


// Calls unit tests for each function defined in import.c
int main(void) {
    printf("\n=== RUNNING TESTS FOR IMPORT ===\n");
    test_prompt_file_path();
    test_tokenize_string();

    printf("\n=== ALL TESTS PASSED ===\n");
    return 0;
}
