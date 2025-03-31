/*
 * Author: Helen Ly
 * Lab instructor: Dhara Wagh
 * Lecture instructor: Dhara Wagh
*/



#include <stdio.h>
#include "DB.h"

#define MAX_SIZE 100

/***********************************************
Purpose: 
Arguments:
Returns: void 
************************************************/


void editTableEntry(int tableID, char* memberName, char* newValue){

    //array to hold key
    char* data[1];
    char specifier[MAX_SIZE];
    snprintf(specifier, sizeof(specifier),"tableID=%d", tableID);

    char kvPair[MAX_SIZE];
    //format string in kvPair as memberNmae=newValue
    snprintf(kvPair, sizeof(kvPair), "%s=%s", memberName, newValue);
    data[0] = kvPair; //asigning the keyvalue pair to first index of data

    char** result = db_update(kvPair, "picnicTable", specifier);

    if (strcmp(result[0], "Success")!= 0)
    {
        fprintf(stderr,"Failed to update table entry.\n");
    }

    
}


