/*
# Student's Name: Maria Reyes
# Assignment #3
# Lab Section: X05L
# Lab Instruction's Name: Dhara Wagh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DB.h"

char* db_delete(char* data, char* tableID, char* specifier)
{
    if(tableID == NULL)
    {
        return "Failure";
    }

    /*Initializing pointer table*/
    Table* target_table = NULL;

    /*Checking tables are exactly the same*/
    if(strcmp(tableID, "tableTypeTable") == 0)
    {
        target_table = tableTypeTable;
    }
    else if(strcmp(tableID, "surfaceMaterialTable") == 0)
    {
        target_table = surfaceMaterialTable;
    }
    else if(strcmp(tableID, "structuralMaterialTable") == 0)
    {
        target_table = structuralMaterialTable;
    }
    else
    {
        /*If it does not match with any of the tables listed*/
        return "Failure";
    }

    /*Deleting all the data from the table*/
    if(data == NULL)
    {
        for(int i = 0; i < INIT_SIZE; i++)
        {
            if(target_table->data[i] != NULL)
            {
                /*Freeing all the data*/
                free(target_table->data[i]);

                /*Empty table*/
                target_table->data[i] = NULL;
            }
        }
        return "Success";
    }

    /*Deleting the specific data*/
    for(int i = 0; i < INIT_SIZE; i++)
    {
        /*Checking for the matched data*/
        if(target_table->data[i] != NULL && strcmp(target_table->data[i], data) == 0)
        {
            /*Freeing the data*/
            free(target_table->data[i]);

            /*Slot is empty*/
            target_table->data[i] = NULL;
            return "Success";
        }
    }
    return "Failure";
}