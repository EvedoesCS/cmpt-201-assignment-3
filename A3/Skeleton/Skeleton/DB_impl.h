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

/***************filename****************
Purpose: Breaks a string into a char * array,
the string being tokenized is expected to contain
words seperated by commas
Arguments: char *line -> the string to tokenize
Returns: void;
**********************************************/
void tokenize_string_impl(char *line, char *tokens[11]); 

int getTableIndex(Table* table, char* value);

//void freePicnicTableR(struct pTableEntry* current);

//void freePicnicTable(PicnicTable* table);

//void freeNeighbourhoodTableR(struct nTableEntry* current);

//void freeNeighbourhoodTable(NeighbourhoodTable* table);

void detokenize_impl(struct pTableEntry *curr, char line[512]); 


#endif
