 /* Author: Eve Leonard
 * Lab instructor: Dhara Wagh
 * Lecture instructor: Abdullah Mohiuddin
 */

#ifndef IMPORT_H
#define IMPORT_H

/***************filename****************
Purpose:
Arguments:
Returns:
**********************************************/

/***************prompt_file_path****************
Purpose: Prompts the user for the name of a file
to read/write csv data from/to. Returns an error
if read value does not end in .csv;
Arguments: char *buffer -> A buffer to write the
filename to;
Returns: void 
**********************************************/
void prompt_file_path(char *buffer);

/***************load_from_file*****************
Purpose: Reads lines from a csv file and loads
them into a database using a db_insert() helper
function;
Arguments: char *filename -> the name of the file
to load from;
Returns: void;
**********************************************/
void load_from_file(char *filename);


/***************filename****************
Purpose: Breaks a string into a char * array,
the string being tokenized is expected to contain
words seperated by commas
Arguments: char *line -> the string to tokenize
Returns: char **tokens
**********************************************/
char **tokenize_string(char *line, char tokens[11][50]); 


/***************filename****************
Purpose:
Arguments:
Returns:
**********************************************/
void write_to_file(char *filename);

#endif
