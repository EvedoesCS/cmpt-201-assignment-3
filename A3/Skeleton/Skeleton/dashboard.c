/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
*/

//You may include other original headers as you see fit
//#include "DB.h"

#include <stdio.h>
#define INPUT_LEN 10
#define FILENAME_LEN 100


void displayMenuOptions(){
    printf("\n");
    printf("Please select your option below (from 1 to 7): \n");
    printf("\n");
    printf("1. Import Database. \n");
    printf("2. Export Database. \n");
    printf("3. Count Entries. \n");
    printf("4. Sort Data By A Member. \n");
    printf("5. Edit an Entry. \n");
    printf("6. Generate Reports. \n");
    printf("7. Exit. \n");
}

void memberNameSelections(){
    printf("Select member name that need to be counted: \n");
    printf("\n");
    printf("1. Table Type. \n");
    printf("2. Surface Material;. \n");
    printf("3. Structural Material. \n");
    printf("4. Neigbourhood ID. \n");
    printf("5. Neighbourhood Name. \n");
    printf("6. Ward. \n");
    printf("7. Exit. \n");
            
}

int main(int argc, char *argv[]){

    displayMenuOptions();
    int cmd = 0;
    //int running = 1;

    char input[INPUT_LEN];

    while (cmd != 7){ //the program keep running until the user choose option 7
        
        if (fgets(input, INPUT_LEN, stdin) != NULL){
            while (strlen(input) != 1){
                fprintf(stderr, "Please only choose one number from 1 to 7.");
                fgets(input, INPUT_LEN, stdin);
            }
            cmd = (int) input;
        }
        else{
            fprintf("No input provided, the program is terminated.");
            exit(0);
        }

        if (cmd == 1){

            char* filename;
            printf("Enter the filename to be imported: ");
            if (fgets(filename, FILENAME_LEN, stdin) != NULL){
                importDB(filename);
                printf("File %s has been imported", filename);
            }
            else {
                exit(0);
            }
        }
        
        if (cmd == 2){
            char* filename;
            printf("Enter the filename to be imported: ");
            if (fgets(filename, FILENAME_LEN, stdin) != NULL){
                exportDB(filename);
                printf("File %s has been exported", filename);

            }
            else {
                exit(0);
            }
        }

        if(cmd == 3){
            memberNameSelections();  
            
            char* memberName [INPUT_LEN];
            int select = 0;

            while (select != 7){
                if (fgets(memberName, INPUT_LEN, stdin) != NULL){
                    select = (int) memberName;
                }
                else{
                    fprintf(stderr, "Please only choose one number from 1 to 7.");
                    fgets(memberName, INPUT_LEN, stdin);
                                }
            }
        
        }
    }


    return 0;
}
