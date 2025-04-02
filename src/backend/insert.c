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

/*Inserting into an array based table*/
char *db_insert(char* data, char* tableID, char* specifier)
{
    /*If data or table are invalid*/
    if (data == NULL || tableID == NULL)
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

    /*Checking if the data already exists in the table*/
    for(int i = 0; i < INIT_SIZE; i++)
    {
        if(target_table->data[i] != NULL && strcmp(target_table->data[i], data) == 0)
        {
            return "Exists";
        }
    }

    /*Adding the data into the table*/
    for(int i = 0; i < INIT_SIZE; i++)
    {
        if(target_table->data[i] == NULL)
        {
            /*Inserting the data at the tail of the array*/
            target_table->data[i] = malloc(strlen(data) + 1);

            /*If malloc fails*/
            if(target_table->data[i] == NULL)
            {
                return "Failure";
            }

            /*Copying the data into the empty space*/
            strcpy(target_table->data[i], data);
            return "Success";
        }
    }

    /*Table is full*/
    return "Failure";
}