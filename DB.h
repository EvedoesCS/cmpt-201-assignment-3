/* DB.h
 * 
 * Public interface to the specification for your database implementation
 *
 * Please do not modify any code in this file!  We will be testing your code
 * under the assumption that the public interface matches this interface.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#ifndef DB_H
#define DB_H

/*
 * DECLARE AND TYPEDEF HERE THE STRUCTS Table, NeighbourhoodTable, AND PicnicTable
 * WHICH WILL BE FIELDS IN THE STRUCT DataBase BELOW. YOU MAY DECLARE ADDITIONAL
 * STRUCTS AS NEEDED.
 */

/*
 * The INIT_SIZE is only relevant if you are using arrays for your data structures. 
 * If you are using linked lists you will not need it
 */
#define INIT_SIZE 5  

typedef char *(*statement)(char *, char *, char*);

typedef struct table{
    char *data[10];
}Table;

struct nTableEntry {
    char *code;
    char *value;
    struct nTableEntry *next; 
};

typedef struct nTable {
    struct nTableEntry *head;
    int size;
}NeighbourhoodTable;

struct pTableEntry {
    int tableId;
    char *id;
    int tableTypeIdx;
    int surfaceMatIdx;
    int structuralMatIdx;
    char *street_ave;
    struct nTableEntry *neighbourhoodId;
    char *ward;
    char *latitude;
    char *longitude;
    char *location;
    struct pTableEntry *next; 
};

typedef struct pTable {
    struct pTableEntry *head;
    int size;
}PicnicTable;

/*
 * You may change the internal details of the struct below,
 * only keep it typedef'ed to DataBase
 */

typedef struct {
    // You can add anything you see fit here
    Table *tableTypeTable;
    Table *surfaceMaterialTable;
    Table *structuralMaterialTable;
    NeighbourhoodTable *neighborhoodTable;
    PicnicTable *picnicTableTable;
} DataBase;

/* Declare a global DataBase variable*/
/* That should be the only global variable declared*/
/* DB.c should have the definition of this variable*/
extern DataBase *Db;

/**********************Backend_Functions*****************************/



/***************************import_db**********************************
Author: Eve Leonard
Purpose: Imports CSV data from a file into a db struct;
Arguments: filename -> file to read from
Returns: void
**********************************************************************/
void importDB(char *filename);


/***************************export_db**********************************
Author: Maria Reyes 
Purpose: Compiles a db struct into lines in CSV format to be written into
a file;
Arguments: filename -> file to write to;
Returns: void
**********************************************************************/
void exportDB(char *filename);

/***************************db_query**********************************
Author: Eve Leonard
Purpose: Parses db commands and calls appropriate helper functions to 
perfrom CRUD (Insert, Select, Update, Delete) functionalities on a db 
struct;
Arguments: 
    stmt -> function pointer which calls the desired operation;
    data -> array of string which need to be added, removed, or selected 
    from the db struct. Expected to follow KV pair format 
    Ex. ["Surface Material=foo", "Ward=bar"]
    data_count -> the number of elements in data, operations will be 
    performed / helper functions will be called "data_count" number of
    times;
    tableID -> The id of the table to perform the opperation on,
    specifier -> optional targets needed to perform a command. For 
    example to select row 4, id=4 will be passed. 
    buffer -> buffer to write the requested data to.

Returns: A string array with the requested data sorted in the same order
as the corresponding items in data were proccessed.
**********************************************************************/
void db_query(statement stmt, char **data, int data_count, char *tableID, char *specifier, char **buffer);

/***************************db_insert**********************************
Author: Maria Reyes
Purpose: Insets a new entry into a table in the db struct; 
Arguments: data -> the data to insert, tableID -> the id of the table
to insert into;
Returns: String with a success or failure message
**********************************************************************/
char *db_insert(char *data, char *tableID, char *specifier);


/***************************db_update**********************************
Author: Matthew Meyer
Purpose: Updates an Item in the db struct in the specified table.
Arguments: 
    data -> the item(s) to update
    tableID -> The id of the table to update in
    specifier -> An optional specifier to target specific columns (fields)
    in tables.
Returns: String with a success or failure message
**********************************************************************/
char *db_update(char *data, char *tableID, char *specifier);

/***************************db_select**********************************
Author: Eve Leonard
Purpose: Finds the requested data in the db struct and returns it in the 
order it was requested in.
Arguments: 
    data -> The data requested in KV pair format ["material_type=wood"]
    tableID -> the id of the table to perform the operation on.
    specifier -> An optional specifer to target specific columns (fields)
    in the table.
Returns: String with a success or failure message
**********************************************************************/
void db_select(char *data[], int data_len, char *specifier, char **buffer, int buffer_len);

/***************************db_delete**********************************
Author: Maria Reyes
Purpose: Removes an item from the db and frees all memory associated 
with it. 
Arguments: 
    data -> the items to remove from the table,
    tableID -> the id of the table to perform the operation on
    specifier -> an optional specifier to target specific entries in
    the table.
Returns: String with a success or failure message
**********************************************************************/
char *db_delete(char *data, char *tableID, char *specifier);

/*
 * Take a tableID, the name of a member of the picnicTable entry and a value for that 
 * member as parameters, and find the entry which has that tableID and 
 * change its memberName value to newValue. 
 * Members that can be modified:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material 
 * If the new value is not found in the existing tables, this value must be added to the 
 * corresponding table.
 */
void editTableEntry(int tableID, char *memberName, char *value);

/***************************countEntries**********************************
Author: Ethan Collier
Purpose: It counts how many entries match a specific memberName and value in the picnicTable
Arguments:
    memberName -> Name of the member to match (e.g., "Ward", "Table Type", "Neighbourhood Name").
    value -> The value to count occurrences of for the given memberName.
Returns: The number of entries that match the specified memberName and value.
**********************************************************************/
int countEntries(char *memberName, char *value);

/***************************sortByMember**********************************
Author: Ethan Collier
Purpose: It sorts the picnicTable by the values of the specified memberName in order
Arguments:
    memberName -> Name of the member to sort by (e.g., "Ward", "Table Type").
Returns: void
**********************************************************************/
void sortByMember(char *memberName);

/***************************reportByNeighbourhood**********************************
Author: Ethan Collier
Purpose: It prints the list of picnic tables grouped by neighborhoods in alphabetical order
Arguments: None
Returns: void
**********************************************************************/
void reportByNeighbourhood();

/***************************reportByWard**********************************
Author: Ethan Collier
Purpose: It prints the list of picnic tables grouped by wards in ascending numerical order
Arguments: None
Returns: void
**********************************************************************/
void reportByWard();



/*
 * Frees all dynamic memory associated with each table upon exit. 
 */
void freeDB();


#endif
