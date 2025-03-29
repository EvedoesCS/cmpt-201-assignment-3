/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */


void importDB(char *filename, DataBase db){}

void exportDB(char *filename, DataBase db){}

void db_query(char *command, char **data, int data_count, char *tableID, char *specifier, char **buffer){
}


char *db_insert(char *data, char *tableID){
    char *msg = "foo";
    return msg;
}

char *db_update(char *data, char *tableID, char *specifier){
    char *msg = "foo";
    return msg;
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
    return 0;
}
