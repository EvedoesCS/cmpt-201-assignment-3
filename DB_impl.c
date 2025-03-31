/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"      /* Import the public database header. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***************prompt_file_path****************
Purpose: Prompts the user for the name of a file
to read csv data from;
Arguments: char *buffer -> A buffer to write the
filename to;
Returns: void 
************************************************/
void prompt_file_path_impl(char *buffer) {
    while (1) {
        // Prompt for filename
        char filename[256];
        printf("Enter the name of the file to read/write to: ");
        scanf("%s", filename);

        // Ensures the file has a .csv extension;
        char extension[5];
        extension[4] = '\0';
        for (int i = (strlen(filename) - 4), j = 0; i < strlen(filename) || j < 3; i++, j++) {
            extension[j] = filename[i]; 
        }
        if (strcmp(extension, ".csv") != 0) {
            printf("Error: Filename must end in '.csv'\n");
        } else {
            strncpy(buffer, filename, strlen(filename));
            break;
        }
    }
}

void tokenize_string_impl(char *line, char *tokens[11]) {
    int wrd_start = 0;
    int wrd_end = 0;
    int idx = 0;

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == 44) {
            wrd_end = i;
            int wrd_size = (wrd_end - wrd_start);

            // Malloc Space for new word and copy data;
            char *new_word = malloc(sizeof(char) * (wrd_size) + 1);
            strncpy(new_word, (line + wrd_start), wrd_size);
            new_word[wrd_size] = '\0';

            tokens[idx] = new_word;
            idx++;

            wrd_start = wrd_end + 1;
        } 
    } 

}
