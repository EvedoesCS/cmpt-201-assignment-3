 /* Author: Eve Leonard
 * Lab instructor: Dhara Wagh
 * Lecture instructor: Abdullah Mohiuddin
 */

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
void prompt_file_path(char *buffer) {
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

void tokenize_string(char *line, char tokens[11][50]) {
    int col = 0;
    int row = 0;
    for (int i = 0; i < strlen(line); i++) { 
        if (line[i] == 44) {
            col++;
            row = 0;
            continue;
        }
        tokens[col][row] = line[i];
        row++;
    }
}


void load_from_file(char *filename) {
    char line[512];
    FILE *f_ptr = fopen(filename, "r");

    while (fgets(line, sizeof(line), f_ptr) != NULL) {
        char tokens[11][50] = {'\0'};

        tokenize_string(line, tokens);

        // TODO 
        // db_query(db, "INSERT", tokens[], "TABLE");

    }

}
