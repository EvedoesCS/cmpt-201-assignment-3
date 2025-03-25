/*
# Student's Name: Maria Reyes
# Assignment #3
# Lab Section: X05L
# Lab Instruction's Name: Dhara Wagh
*/

#include <stdio.h>
#include <string.h>
#include "DB.h"

void exportDB(const char* filename)
{
    FILE* fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Cannot open %s\n", filename);
        return;
    }

    /*Pointer to current node*/
    Table* current_node;

    /*Exporting the Table Type Table of the linked list*/
    current_node = Db->tableTypeTable;
    
    /*Iterating until the end of the linked list*/
    while(current_node != NULL)
    {
        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
        current_node = current_node->next;
    }

    /*Exporting the Surface Material Table of the linked list*/
    current_node = Db->surfaceMaterialTable;

    /*Iterating until the end of the linked list*/    
    while(current_node != NULL)
    {
        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
        current_node = current_node->next;
    }

    /*Exporting the Structural Material Table of the linked list*/
    current_node = Db->structuralMaterialTable;
    
    /*Iterating until the end of the linked list*/
    while(current_node != NULL)
    {
        fprintf(fp, "%d, %s\n", current_node->id, current_node->value);
        current_node = current_node->next;
    }

    /*Close file*/
    fclose(fp);
}