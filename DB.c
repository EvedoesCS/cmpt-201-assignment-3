/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

DataBase *Db;

/******************************************************************
Author: Matthew Meyer Eve Leonard;
Purpose: Initializes the global variable Db used to access the database;
Arguments: void;
Returns: void;
 *******************************************************************/
void db_create() {
    Db = malloc(sizeof(DataBase));
    if (Db == NULL) {
        printf("ERROR: DataBase Creation Failed\n");
        return;
    }

    Db->tableTypeTable = malloc(sizeof(struct table));
    if (Db->tableTypeTable == NULL) {
        printf("ERROR: Failed to initialize a table\n");
        return;
    }
    Db->surfaceMaterialTable = malloc(sizeof(struct table));
    if (Db->surfaceMaterialTable == NULL) {
        printf("ERROR: Failed to initialize a table\n");
        return;
    }
    Db->structuralMaterialTable = malloc(sizeof(struct table));
    if (Db->structuralMaterialTable == NULL) {
        printf("ERROR: Failed to initialize a table\n");
        return;
    }
    Db->neighborhoodTable = malloc(sizeof(struct nTable));
    if (Db->neighborhoodTable == NULL) {
        printf("ERROR: Failed to initialize a table\n");
        return;
    }
    Db->picnicTableTable = malloc(sizeof(struct pTable));
    if (Db->picnicTableTable == NULL) {
        printf("ERROR: Failed to initialize a table\n");
        return;
    }
    Db->picnicTableTable->size = 0;
    Db->picnicTableTable->head = NULL;

    for (int i = 0; i < 10; i++) {
        Db->tableTypeTable->data[i] = NULL;
        Db->surfaceMaterialTable->data[i] = NULL;
        Db->structuralMaterialTable->data[i] = NULL;
    }

    Db->neighborhoodTable->head = NULL;
    Db->neighborhoodTable->size = 0;
}

/******************************************************************
Author: Eve Leonard;
Purpose: Initializes the lookup tables for the database;
Arguments: table -> A pointer to the lookup table to initialize
            value -> The value to insert in the table;
Returns: void
 *******************************************************************/
void init_lookupTable(Table *table, char *value) {
    // Looks for a 
    for (int i = 0; i < 10; i++) {
        // Insert value and return if empty idx
        // found;
        if (table->data[i] == NULL) 
        {
            table->data[i] = value;
            return;
        } 
        // Return early if value found in array;
        else if (strcmp(table->data[i], value) == 0) 
        {
            free(table->data[i]);
            table->data[i] = value;
            return;
        }
    }
}

/******************************************************************
Author: Eve Leonard;
Purpose: initializes the neighborhood table with values from a csv 
file line;
Arguments: nTable -> A pointer to the neightborhood table;
           code -> A numerical table id from the data;
           value -> the name of a neighborhood from the data;
Returns: void;
 *******************************************************************/
void init_nTable(NeighbourhoodTable *nTable, char *code, char *value) {
    struct nTableEntry *curr = nTable->head;

    // Checks if neighbourhood is already in the
    // lookup table;
    if (nTable->head != NULL) {
        while (curr->next != NULL) {
            if (strcmp(curr->next->code, code) == 0) {
                free(curr->next->code);
                free(curr->next->value);
                curr->next->code = code;
                curr->next->value = value;
                return;
            }
            curr = curr->next;
        }
    }

    // Init a new table entry node;
    struct nTableEntry *new_node = malloc(sizeof(struct nTableEntry));
    new_node->code = code;
    new_node->value = value;
    new_node->next = NULL;

    // Place new node in the neighbourhood linked list;
    if (nTable->head == NULL) {
        nTable->head = new_node;
        return;
    }
    curr->next = new_node; 

    nTable->size++;
}

/******************************************************************
Author: Eve Leonard;
Purpose: Imports a csv file into the database accessed through the 
global variable Db which must be initialized with the function 
db_create();
Arguments: filename -> The path to the .csv file to import;
Returns: void;
 *******************************************************************/
void importDB(char *filename) {
    char line[256];
    FILE *f_ptr = fopen(filename, "r");

    // Consume the first line in the file;
    fgets(line, sizeof(line), f_ptr);

    while (fgets(line, sizeof(line), f_ptr) != NULL) {
        // Create space to fit tokenized line;
        char *tokens[11];

        // Break line into tokens;
        tokenize_string_impl(line, tokens);

        // Initialize Db with values;
        init_lookupTable(Db->tableTypeTable, tokens[1]);
        init_lookupTable(Db->surfaceMaterialTable, tokens[2]);
        init_lookupTable(Db->structuralMaterialTable, tokens[3]);

        // Init the neighbourhood table with data;
        init_nTable(Db->neighborhoodTable, tokens[5], tokens[6]);
        Db->neighborhoodTable->size++;

        struct pTableEntry *new_entry = malloc(sizeof(struct pTableEntry));
        new_entry->tableId = Db->picnicTableTable->size;
        new_entry->id = tokens[0];

        if (tokens[1] != NULL) {
            new_entry->tableTypeIdx = getTableIndex(Db->tableTypeTable, tokens[1]);
        }
        if (tokens[2] != NULL) {
            new_entry->surfaceMatIdx = getTableIndex(Db->surfaceMaterialTable, tokens[2]);
        }
        if (tokens[3] != NULL) {
            new_entry->structuralMatIdx = getTableIndex(Db->structuralMaterialTable, tokens[3]);
        }

        new_entry->street_ave = tokens[4];

        struct nTableEntry *nCurr = Db->neighborhoodTable->head;
        while (nCurr != NULL) {
            if (strcmp(nCurr->code, tokens[5]) == 0) {
                new_entry->neighbourhoodId = nCurr;
            }
            nCurr = nCurr->next;
        }

        new_entry->ward = tokens[7];
        new_entry->latitude = tokens[8];
        new_entry->longitude = tokens[9];

        new_entry->location = tokens[10];
        
        new_entry->next = NULL;

        // Insert new_entry into the DB;
        if (Db->picnicTableTable->head == NULL ) {
            Db->picnicTableTable->head = new_entry;
        }
        else {
            struct pTableEntry *curr = Db->picnicTableTable->head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = new_entry;
        }

        Db->picnicTableTable->size++;
    }

    fclose(f_ptr);
}

void exportDB(char *filename){
    FILE* fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Cannot open %s\n", filename);
        return;
    }

    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");

    struct pTableEntry *curr = Db->picnicTableTable->head; 

    while (curr != NULL) {
        char line[256] = {0};
        detokenize_impl(curr, line);
        fputs(line, fp);

        curr = curr->next;
    }



    /*Close file*/
    fclose(fp);

}


char *db_update(char *data, char *tableID, char *specifier){
    //find tableid
    
    struct pTableEntry* temp = Db->picnicTableTable->head;
    int tableId = atoi(tableID);

    if (temp == NULL) {
        return "Failure: picnicTableTable has no entries.";
    }

    while (temp != NULL) {
        if (temp->tableId == tableId) {
            //If we reach here, we have found our table ID
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL) {
        //printf("tableID not found. Unable to edit entry.\n");
        return "Failure: TableID not found.";
    }
    
    //Compare memberName so we can select the table to insert into
    if (strcmp(specifier, "Table Type") == 0) {
        //printf("T - Table Type Selected!\n");
        int index = getTableIndex(Db->tableTypeTable, data);
        if (index > 10) {
            return "Failure: Could not find data in tableTypeTable.";
        }
        temp->tableTypeIdx = index;
        return "Success\n";

    } else if (strcmp(specifier, "Surface Material") == 0) {
        //printf("T - Surface Material Selected!\n");
        int index = getTableIndex(Db->surfaceMaterialTable, data);
        if (index > 10) {
            return "Failure: Could not find data in surfaceMaterialTable.";
        }
        temp->tableTypeIdx = index;
        return "Success";

    } else if (strcmp(specifier, "Structural Material") == 0) {
        //printf("T - Structural Material Selected!\n");
        int index = getTableIndex(Db->structuralMaterialTable, data);
        if (index > 10) {
            return "Failure: Could not find data in structuralMaterialTable.";
        }
        temp->tableTypeIdx = index;
        return "Success";
    }

    return "Failure: Could not find given member.";
}

void freeDB() {
    for (int i = 0; i < 10; i++) {
        if (Db->tableTypeTable->data[i] != NULL) {
            free(Db->tableTypeTable->data[i]);
        }
        if (Db->surfaceMaterialTable->data[i] != NULL) {
            free(Db->surfaceMaterialTable->data[i]);

        }
        if (Db->structuralMaterialTable->data[i] != NULL) {
            free(Db->structuralMaterialTable->data[i]);
        }
    }

    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);

    freeNeighbourhoodTable(Db->neighborhoodTable);
    freePicnicTable(Db->picnicTableTable);
    free(Db);
}

int main(void) {
    db_create();

    char *filename = "./src/backend/dataset/PicnicTable.csv"; 
    importDB(filename);

    exportDB("out.csv");

    freeDB();

    return 0;
}
