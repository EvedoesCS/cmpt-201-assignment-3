/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#ifndef DB_IMPL_H
#define DB_IMPL_H

#include "DB.h"

/***************prompt_file_path****************
Purpose: Prompts the user for the name of a file
to read/write csv data from/to. Returns an error
if read value does not end in .csv;
Arguments: char *buffer -> A buffer to write the
filename to;
Returns: void 
**********************************************/
void prompt_file_path_impl(char *buffer);

/***************tokenize_string_impl****************
Purpose: Breaks a string into a char * array,
the string being tokenized is expected to contain
words seperated by commas
Arguments: char *line -> the string to tokenize
           char *tokens[11] -> the buffer to store
           the tokens;
Returns: void;
**********************************************/
void tokenize_string_impl(char *line, char *tokens[11]); 

/***************detokenize_impl****************
Purpose:
Arguments:
Returns:
**********************************************/
void detokenize_impl(struct pTableEntry *curr, char line[256]); 

 /***************getTableIndex****************
 Author: Matthew Meyer;
 Purpose: Searches the data of a given table for a given
 value, then returns the index of that value if found.
 Arguments: Table* table -> the Table with the data we
 want to search; char* value -> the value to search for.
 Returns: The index of value in table if value could be found,
 11 otherwise.
 ************************************************/
int getTableIndex(Table* table, char* value);

 /***************freePicnicTableR****************
 Author: Matthew Meyer;
 Purpose: Called by freePicnicTable to recursively
 free a picnicTable table.
 Arguments: struct pTableEntry* current -> the Entry
 in the picnicTable to be individually freed.
 Returns: void.
 ************************************************/
void freePicnicTableR(struct pTableEntry* current);

 /***************freePicnicTable****************
 Author: Matthew Meyer;
 Purpose: Calls freePicnicTableR to free a picnicTable table
 Arguments: PicnicTable* Table -> The picnicTable to be freed
 Returns: void
 ************************************************/
void freePicnicTable(PicnicTable* table);

 /***************freeNeighbourhoodTableR****************
 Author: Matthew Meyer;
 Purpose: Called by freeNeighbourhoodTable to recursively
 free a NeighbourhoodTable table.
 Arguments: struct nTableEntry* current -> the Entry
 in the NeighbourhoodTable to be individually freed.
 Returns: void.
 ************************************************/
void freeNeighbourhoodTableR(struct nTableEntry* current);

 /***************freeNeighbourhoodTable****************
 Author: Matthew Meyer;
 Purpose: Calls freeNeighbourhoodTableR to free a NeighbourhoodTable table
 Arguments: NeighbourhoodTable* Table -> The NeighbourhoodTable to be freed
 Returns: void
 ************************************************/
void freeNeighbourhoodTable(NeighbourhoodTable* table);

/***************************cmpTableType**********************************
Author: Ethan Collier
Purpose: It compares the values for the table type from two picnic table entries in order
Arguments:
    const void *a -> Pointer to the first picnic table entry
    const void *b -> Pointer to the second picnic table entry
Returns:
    Integer value from comparison (1, 0 or -1)
**********************************************************************/
int cmpTableType(const void *a, const void *b);
/***************************cmpSurfaceMaterial**********************************
Author: Ethan Collier
Purpose: It compares the values for the surface material from two picnic table entries in order
Arguments:
    const void *a -> Pointer to the first picnic table entry
    const void *b -> Pointer to the second picnic table entry
Returns:
    Integer value from comparison (1, 0 or -1)
**********************************************************************/
int cmpSurfaceMaterial(const void *a, const void *b);
/***************************cmpStructuralMaterial**********************************
Author: Ethan Collier
Purpose: It compares the values for the structural materials from two picnic table entries in order
Arguments:
    const void *a -> Pointer to the first picnic table entry
    const void *b -> Pointer to the second picnic table entry
Returns:
    Integer value from comparison (1, 0 or -1)
**********************************************************************/
int cmpStructuralMaterial(const void *a, const void *b);
/***************************cmpNeighborhoodName**********************************
Author: Ethan Collier
Purpose: It compares the values for the neighborhood names from two picnic table entries in order
Arguments:
    const void *a -> Pointer to the first picnic table entry
    const void *b -> Pointer to the second picnic table entry
Returns:
    Integer value from comparison (1, 0 or -1)
**********************************************************************/
int cmpNeighborhoodName(const void *a, const void *b);
/***************************cmpNeighborhoodName**********************************
Author: Ethan Collier
Purpose: It compares the values for the wards from two picnic table entries in order
Arguments:
    const void *a -> Pointer to the first picnic table entry
    const void *b -> Pointer to the second picnic table entry
Returns:
    Integer value from comparison (1, 0 or -1)
**********************************************************************/
int cmpWard(const void *a, const void *b);

// Helper function to display menu options for count entries;
void countEntriesOptions();

#endif
