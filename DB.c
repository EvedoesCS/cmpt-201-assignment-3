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
                printf("Ommiting duplicate\n");
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
    char line[512];
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
    }
}

//void exportDB(char *filename){
//    FILE* fp = fopen(filename, "w");
//
//    if(fp == NULL)
//    {
//        printf("Cannot open %s\n", filename);
//        return;
//    }
//
//    /*Pointer to current node*/
//    Table* current_node;
//
//    /*Exporting the Table Type Table of the linked list*/
//    current_node = Db->tableTypeTable;
//    
//    /*Iterating until the end of the linked list*/
//    while(current_node != NULL)
//    {
//        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
//        current_node = current_node->next;
//    }
//
//    /*Exporting the Surface Material Table of the linked list*/
//    current_node = Db->surfaceMaterialTable;
//
//    /*Iterating until the end of the linked list*/    
//    while(current_node != NULL)
//    {
//        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
//        current_node = current_node->next;
//    }
//
//    /*Exporting the Structural Material Table of the linked list*/
//    current_node = Db->structuralMaterialTable;
//    
//    /*Iterating until the end of the linked list*/
//    while(current_node != NULL)
//    {
//        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
//        current_node = current_node->next;
//    }
//
//    /*Close file*/
//    fclose(fp);

//}

void db_query(statement stmt, char **data, int data_count, char *tableID, char *specifier, char **buffer){
    for (int i = 0; i < data_count; i++) {
        buffer[i] = stmt(data[i], tableID, specifier);
    } 
}


char *db_insert(char *data, char *tableID, char *specifier){
    char *msg = "foo";
    return msg;
}

char *db_update(char *data, char *tableID, char *specifier){
    //find tableid
    
    struct pTableEntry* temp = Db->picnicTableTable->head;
    int tableId = atoi(tableID);

    if (temp == NULL) {
        //printf("PicnicTableTable has no entries!\n");
        return "Failure";
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
        return "Failure";
    }
    
    //Compare memberName so we can select the table to insert into
    if (strcmp(specifier, "Table Type") == 0) {
        //printf("T - Table Type Selected!\n");
        temp->tableTypeId = getTableIndex(Db->tableTypeTable, data, temp->tableTypeId);
        return "Success";

    } else if (strcmp(specifier, "Surface Material") == 0) {
        //printf("T - Surface Material Selected!\n");
        temp->tableTypeId = getTableIndex(Db->surfaceMaterialTable, data, temp->tableTypeId);
        return "Success";

    } else if (strcmp(specifier, "Structural Material") == 0) {
        //printf("T - Structural Material Selected!\n");
        temp->tableTypeId = getTableIndex(Db->structuralMaterialTable, data, temp->tableTypeId);
        return "Success";
    }
    return "Failure";
}

char *db_select(char *data, char *tableID, char *specifier){
    char *msg = "foo";
    return msg;
}

char *db_delete(char *data, char *tableID, char *specifier){
    char *msg = "foo";
    return msg;
}

int main(void) {
    db_create();

    char *filename = "./src/backend/dataset/PicnicTableSmall.csv"; 
    importDB(filename);

    printf("%s\n", Db->tableTypeTable->data[0]);
    printf("%s\n", Db->neighborhoodTable->head->next->next->next->value);

    return 0;
}
