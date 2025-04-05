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
    // Allocate memory for the DB;
    Db = malloc(sizeof(DataBase));
    if (Db == NULL) {
        printf("ERROR: DataBase Creation Failed\n");
        return;
    }

    // Allocate memory for each lookup table and check
    // malloc was successfull;
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

    // Initializes picnicTable members;
    Db->picnicTableTable->size = 0;
    Db->picnicTableTable->head = NULL;

    // Initializes lookup table arrays to NULL;
    for (int i = 0; i < 10; i++) {
        Db->tableTypeTable->data[i] = NULL;
        Db->surfaceMaterialTable->data[i] = NULL;
        Db->structuralMaterialTable->data[i] = NULL;
    }

    // Initializes members for neighbourhoodTable;
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
    // Creates file ptr and variable to store lines;
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

        // Allocate space for a new picnicTable entry;
        struct pTableEntry *new_entry = malloc(sizeof(struct pTableEntry));
        new_entry->tableId = Db->picnicTableTable->size;
        new_entry->id = tokens[0];

        // Determine the indexes of table type, surface material and structural
        // material in their respective lookup tables and place the value
        // into the new entry;
        new_entry->tableTypeIdx = getTableIndex(Db->tableTypeTable, tokens[1]);
        new_entry->surfaceMatIdx = getTableIndex(Db->surfaceMaterialTable, tokens[2]);
        new_entry->structuralMatIdx = getTableIndex(Db->structuralMaterialTable, tokens[3]);

        new_entry->street_ave = tokens[4];

        // Initialize the neighbourhoodTableID and neighbourhoodTableName columns
        // from the dataset;
        struct nTableEntry *nCurr = Db->neighborhoodTable->head;
        while (nCurr != NULL) {
            if (strcmp(nCurr->code, tokens[5]) == 0) {
                new_entry->neighbourhoodId = nCurr;
            }
            nCurr = nCurr->next;
        }

        // Initializes the location members;
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

        // Increment size used to mark the ID of the entry;
        Db->picnicTableTable->size++;
    }

    // Close the file pointer when iteration is finished.
    fclose(f_ptr);
}


void exportDB(char *filename){
    // Open file pointer in writing mode and check for errors;
    FILE* fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Cannot open %s\n", filename);
        return;
    }

    // Print the .csv collumn labels;
    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");

    // Iterate over each entry in the picnic table and detokenize the 
    // members into a line to be written to the file;
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


/******************************************************************
Author: Matthew Meyer;
Purpose: Updates one of three specific members of the PicnicTable within
the global DataBase Db
Arguments: char* data -> the data to update; char* tableID -> the unique
ID number of the PicnicTableEntry; char* specifier -> the member of the
PicnicTable to be updated. Acceptable specifiers are as follows:
"Table Type", "Surface Material", "Structural Material";
Returns: A message indicating Failure or Success
*******************************************************************/
void editTableEntry(int tableID, char *memberName, char *value){
    //find tableid
    
    struct pTableEntry* temp = Db->picnicTableTable->head;

    if (temp == NULL) {
        return;
    }

    while (temp != NULL) {
        if (temp->tableId == tableID) {
            //If we reach here, we have found our table ID
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL) {
        //printf("tableID not found. Unable to edit entry.\n");
        return;
    }
    
    //Compare memberName so we can select the table to insert into
    if (strcmp(memberName, "tableTypeId") == 0) {
        //printf("T - Table Type Selected!\n");
        int index = getTableIndex(Db->tableTypeTable, value);
        if (index > 10) {
            return;
        }
        temp->tableTypeIdx = index;
        return;

    } else if (strcmp(memberName, "surfaceMaterialId") == 0) {
        //printf("T - Surface Material Selected!\n");
        int index = getTableIndex(Db->surfaceMaterialTable, value);
        if (index > 10) {
            return;
        }
        temp->surfaceMatIdx = index;
        return;

    } else if (strcmp(memberName, "structuralMaterialId") == 0) {
        //printf("T - Structural Material Selected!\n");
        int index = getTableIndex(Db->structuralMaterialTable, value);
        if (index > 10) {
            return;
        }
        temp->structuralMatIdx = index;
        return;
    }

    return;
}

/******************************************************************
 Author: Ethan Collier
 Purpose: It counts the number of entries in the PicnicTable that match
 a specific memberName and value within Db
 Arguments:
    char* memberName -> Name of the member to search for (e.g., "Ward",
    "Table Type");
    char* value -> The value to match the entries against for the memberName;
 Returns: The number of entries that match the given memberName and value.
 *******************************************************************/
 int countEntries(char *memberName, char *value) {
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return 0;
    }

    int count = 0;
    struct pTableEntry *current = Db->picnicTableTable->head; 

    while (current) {
        if (strcmp(memberName, "Table Type") == 0 && 
            strcmp(Db->tableTypeTable->data[current->tableTypeIdx], value) == 0) { //It uses strcmp to check for matches based on the memberName and value
            count++;
        } else if (strcmp(memberName, "Surface Material") == 0 &&
                   strcmp(Db->surfaceMaterialTable->data[current->surfaceMatIdx], value) == 0) {
            count++;
        } else if (strcmp(memberName, "Structural Material") == 0 &&
                   strcmp(Db->structuralMaterialTable->data[current->structuralMatIdx], value) == 0) {
            count++;
        } else if (strcmp(memberName, "Neighborhood Name") == 0 &&
                   current->neighbourhoodId && strcmp(current->neighbourhoodId->value, value) == 0) {
            count++;
        } else if (strcmp(memberName, "Ward") == 0 &&
                   strcmp(current->ward, value) == 0) {
            count++;
        }
        current = current->next;
    }

    return count;
}
/******************************************************************
Author: Ethan Collier
Purpose: It sorts the PicnicTable within Db by the
values of the specified memberName in ascending order. "Ward" will
be sorted numerically, while others will be sorted alphabetically
Arguments:
   char* memberName -> Name of the member to sort by (e.g., "Ward",
   "Table Type", "Neighbourhood Name");
Returns: void
*******************************************************************/
void sortByMember(char *memberName) {
   if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
       printf("Error: Database is not initialized or empty.\n");
       return;
   }

   int size = Db->picnicTableTable->size;
   
   struct pTableEntry **array = malloc(size * sizeof(struct pTableEntry *)); //This creates an array that'll be used for sorting
   if (!array) {
       printf("Error: Memory allocation failed.\n");
       return;
   }

   struct pTableEntry *current = Db->picnicTableTable->head; 
   for (int i = 0; i < size; i++) {
       array[i] = current;
       current = current->next;
   }

   int (*compare)(const void *, const void *) = NULL;

   if (strcmp(memberName, "Table Type") == 0) { 
       compare = cmpTableType; //Calls the comparison functions from DB_impl
   } else if (strcmp(memberName, "Surface Material") == 0) {
       compare = cmpSurfaceMaterial;
   } else if (strcmp(memberName, "Structural Material") == 0) {
       compare = cmpStructuralMaterial;
   } else if (strcmp(memberName, "Neighbourhood Name") == 0) {
       compare = cmpNeighborhoodName;
   } else if (strcmp(memberName, "Ward") == 0) {
       compare = cmpWard;
   }

   if (!compare) {
       printf("Error: Unknown member name '%s'.\n", memberName);
       free(array);
       return;
   }

   qsort(array, size, sizeof(struct pTableEntry *), compare);

   Db->picnicTableTable->head = array[0]; //It constructs the linked list from the sorted array
   current = Db->picnicTableTable->head;
   for (int i = 1; i < size; i++) {
       current->next = array[i];
       current = current->next;
   }
   current->next = NULL;

   free(array);

   printf("Successfully sorted by %s.\n", memberName);
}
/******************************************************************
Author: Ethan Collier;
Purpose: It prints a listing of PicnicTable entries grouped by wards
in ascending numerical order from Db
Arguments: None
Returns: void
*******************************************************************/
void reportByWard() {
   sortByMember("Ward");
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return;
    }

    struct pTableEntry *current = Db->picnicTableTable->head;

    printf("\n--- Report by Ward ---\n");
    while (current != NULL) {
        printf("Ward: %s\n ID: %s\n Table Type: %s\n Surface Material: %s\n Structural Material: %s\n Street: %s\n Neighbourhood Name: %s\n Latitude: %s\n Longitude: %s\n\n",
               current->ward,
               current->id,
               Db->tableTypeTable->data[current->tableTypeIdx],
               Db->surfaceMaterialTable->data[current->surfaceMatIdx],
               Db->structuralMaterialTable->data[current->structuralMatIdx],
               current->street_ave,
               current->neighbourhoodId->value,
               current->latitude,
               current->longitude);
        current = current->next;
    }
}
/******************************************************************
Author: Ethan Collier
Purpose: It prints a listing of PicnicTable entries grouped by neighbourhoods
in ascending alphabetical order from Db
Arguments: None
Returns: void
*******************************************************************/
void reportByNeighbourhood() {
   sortByMember("Neighbourhood Name");
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return;
    }
    struct pTableEntry *current = Db->picnicTableTable->head;

    printf("\n--- Report by Neighbourhood ---\n");
    while (current != NULL) {
        printf("Neighbourhood Name: %s\n ID: %s\n Table Type: %s\n Surface Material: %s\n Structural Material: %s\n Street: %s\n Ward: %s\n Latitude: %s\n Longitude: %s\n\n",
               current->neighbourhoodId->value,
               current->id,
               Db->tableTypeTable->data[current->tableTypeIdx],
               Db->surfaceMaterialTable->data[current->surfaceMatIdx],
               Db->structuralMaterialTable->data[current->structuralMatIdx],
               current->street_ave,
               current->ward,
               current->latitude,
               current->longitude);
        current = current->next;
    }
}


/******************************************************************
Author: Matthew Meyer;
Purpose: Frees the entire database
Arguments: None
Returns: void
*******************************************************************/
void freeDB() {
    // Free the lookup table elements;
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

    // Free lookup table structs;
    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);

    // Calls recursive free'ing helper functions
    // to free dynamic memory created by linked
    // lists.
    freeNeighbourhoodTable(Db->neighborhoodTable);
    freePicnicTable(Db->picnicTableTable);
    free(Db);
}
