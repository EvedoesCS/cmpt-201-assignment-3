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
    int comma_count = 0;

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == 44) {
            comma_count++;
            if (comma_count != 11) {
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
        wrd_end = strlen(line);
        int wrd_size = (wrd_end - wrd_start);

        // Malloc Space for new word and copy data;
        char *new_word = malloc(sizeof(char) * (wrd_size) + 1);
        strncpy(new_word, (line + wrd_start), wrd_size);
        new_word[wrd_size] = '\0';

        tokens[idx] = new_word;

    } 

}

void detokenize_impl(struct pTableEntry *curr, char line[512]) {
    strcat(line, curr->id);
    strcat(line, ",");
    strcat(line, Db->tableTypeTable->data[curr->tableTypeIdx]);
    strcat(line, ",");
    strcat(line, Db->surfaceMaterialTable->data[curr->surfaceMatIdx]);
    strcat(line, ",");
    strcat(line, Db->structuralMaterialTable->data[curr->structuralMatIdx]);
    strcat(line, ",");
    strcat(line, curr->street_ave);
    strcat(line, ",");
    strcat(line, curr->neighbourhoodId->code);
    strcat(line, ",");
    strcat(line, curr->neighbourhoodId->value);
    strcat(line, ",");
    strcat(line, curr->ward);
    strcat(line, ",");
    strcat(line, curr->latitude);
    strcat(line, ",");
    strcat(line, curr->longitude);
    strcat(line, ",");
    strcat(line, curr->location);
}

/***************getTableIndex****************
Author: Matthew Meyer;
Purpose: Searches the data of a given table for a given
value, then returns the index of that value if found.
Arguments: Table* table -> the Table with the data we
want to search; char* value -> the value to search for.
Returns: The index of value in table if value could be found,
11 otherwise.
************************************************/
int getTableIndex(Table* table, char* value) { //Gets the index of a given string in a table's array
    if (table == NULL) {
        printf("Table is NULL! Unable to get index!\n");
    }
    
    int i = 0;
    while (table->data[i] != NULL) {
        //printf("i = %d\n", i);
        if (strcmp(value, table->data[i]) == 0) {
            //printf("Found %s at index %d\n", value, i);
            return i;
        }
        i++;
    }
    
    return 11; //This means that we can't find it
}

/***************freePicnicTableR****************
Author: Matthew Meyer;
Purpose: Called by freePicnicTable to recursively
free a picnicTable table.
Arguments: struct pTableEntry* current -> the Entry
in the picnicTable to be individually freed.
Returns: void.
************************************************/
void freePicnicTableR(struct pTableEntry* current) {
    if (current == NULL) { //Base case
        return;
    }

    freePicnicTableR(current->next);

    free(current->id);
    current->id = NULL;
    free(current->street_ave);
    current->street_ave = NULL;
    free(current->ward);
    current->ward = NULL;
    free(current->latitude);
    current->latitude = NULL;
    free(current->longitude);
    current->longitude = NULL;
    free(current->location);
    current->location = NULL;

    free(current);
    
    current = NULL;
}

/***************freePicnicTable****************
Author: Matthew Meyer;
Purpose: Calls freePicnicTableR to free a picnicTable table
Arguments: PicnicTable* Table -> The picnicTable to be freed
Returns: void
************************************************/
void freePicnicTable(PicnicTable* table) {
    freePicnicTableR(table->head);
    free(table);
}

/***************freeNeighbourhoodTableR****************
Author: Matthew Meyer;
Purpose: Called by freeNeighbourhoodTable to recursively
free a NeighbourhoodTable table.
Arguments: struct nTableEntry* current -> the Entry
in the NeighbourhoodTable to be individually freed.
Returns: void.
************************************************/
void freeNeighbourhoodTableR(struct nTableEntry* current) {
    if (current == NULL) { //Base case
        return;
    }

    freeNeighbourhoodTableR(current->next);
    free(current->code);
    free(current->value);
    free(current);
    
    current = NULL;
}


/***************freeNeighbourhoodTable****************
Author: Matthew Meyer;
Purpose: Calls freeNeighbourhoodTableR to free a NeighbourhoodTable table
Arguments: NeighbourhoodTable* Table -> The NeighbourhoodTable to be freed
Returns: void
************************************************/
void freeNeighbourhoodTable(NeighbourhoodTable* table) {
    freeNeighbourhoodTableR(table->head);
    free(table);
}