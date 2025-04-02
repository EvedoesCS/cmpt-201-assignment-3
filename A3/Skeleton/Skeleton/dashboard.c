/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Helen Ly
 * Lab instructor: Dhara Wagh
 * Lecture instructor: Dhara Wagh
 * 
 * Disclaimer: Using atoi() function from stdlib.h 
 * to read a representation of a whole number from a string and returns its value.
 * from link: https://www.w3schools.com/c/ref_stdlib_atoi.php#:~:text=The%20atoi()%20function%20reads,not%20part%20of%20the%20number.
*/


//You may include other original headers as you see fit

#include <stdio.h>
#include <stdlib.h> //use for atoi()
#include <string.h> //used for strlen 
#include "DB.h"
//#include "export.c"//TOBEREMOVED - move it to db.c
//#include "editTableEntry.c"//TOBEREMOVED - move to db.c


#define INPUT_LEN 10 //maxlen when selecting menu options
#define FILENAME_LEN 512 //maxlen for filename
#define MAX_LEN 256//maxlen for any buffers 


/*********************************************************************
Author: Helen Ly
Purpose: displaying main menu 
Arguments: void
Returns: void
**********************************************************************/
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

/*********************************************************************
Author: Helen Ly
Purpose: displaying menu for memberName options and prompt user input to be used for 
         option 3 in main menu - count entries
Arguments: void
Returns: memberName string based on user input
**********************************************************************/
//char* memberNameforCountEntries(){
//     //string array of memberName options
//     char* options[6]= {"Table Type", "Surface Material", "Structural Material","Neighborhood ID","Neighborhood Name", "Ward"};
//     printf("Select member name that need to be counted: \n");
//     //loop through the array to display memberName menu
//     for (int i =0; i<6; i++){
//         printf("%d. %s\n", i+1, options[i]);
//     }
    
//     char memberName[INPUT_LEN];
//     int select = 0;

//     while (select<1 || select >6){
//         //when input successfully, the input will be cast to be an int with under select variable
//         if (fgets(memberName, INPUT_LEN, stdin) != NULL){
//             select = atoi(memberName);
//         }
//         //when input is NULL, display error message and prompt user input again
//         else{
//             fprintf(stderr, "Please only choose one number from 1 to 7.\n");
//         }

//         //different return strings based on user input
//         if (select >= 1 && select <= 6){
//             return (options[select-1]);
//         }
       
//         //when input is not within the menu option, print error message and ask for input again
//         else{
//             printf("Selection was invalid, please select a number from 1 to 7.\n");
//             //fgets(memberName, INPUT_LEN, stdin);  
//             //select = atoi(memberName);
              
//         }
//     return NULL;       
// }

/*------------------------------------------------------------------------
Author: Helen Ly
Purpose: displaying menu for memberName options and prompt user input
         to be used in option 4 of main menu - sort member
Arguments: void
Returns: memberName string based on user input
------------------------------------------------------------------------*/

char* memberNameforSortbyMember(){
    char* options[5] = {"Table Type", "Surface Material", "Structural Material", "Neighborhood Name", "Ward"};

    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }

    char memberName[INPUT_LEN];
    int select = 0;

    while (select < 1 || select > 5) {
        if (fgets(memberName, INPUT_LEN, stdin) != NULL) {
            select = atoi(memberName);
        }
        if (select >= 1 && select <= 5) {
            return options[select - 1];
        } else {
            printf("Selection was invalid, please select a number from 1 to 5.\n");
        }
    }
    return NULL;
}


/*********************************************************************
Author: Helen Ly
Purpose: get user input to get memberName
Arguments: void
Returns: string of valid memberName or NULL
**********************************************************************/
char* memberNameforEditEntryOptions(){
    //display menu by looping through the report type options
    char* options[3] = {"Table Type", "Surface Material", "Structural Material"};
    printf("Select the memberName that can be modified: \n");
    for (int i =0; i<3;i++){
        printf("%d. %s", i+1, options[i]);
    }
    int select;
    //if user input NULL or more than a number, print error message

    if (scanf ("%d", &select) !=1 ||select <1 || select >3){
        printf ("The selection is invalid. Choose a number from 1 to 3.\n");
    }
    if (select>=1 && select <= 3){
        return options[select-1];
    }
    return NULL;
    
}

/*
//function prototypes
void countEntriesOptions(); 
void sortByOptions();
void editEntryOptions();
*/


// use as condition to Prevent operations until the database is imported 
int DatabaseImported = 0; //Database hasn't been imported


int main() {

    int cmd = 0;

    char input[INPUT_LEN];

    while (cmd != 7){ //the program keep running until the user choose option 7
        displayMenuOptions();
        if (fgets(input, INPUT_LEN, stdin) != NULL){
            for (int i=0; i<INPUT_LEN; i++){
                if (input[i] == '\n'){
                    input[i] = '\0';
                    break;
                }
            }
            while (strlen(input) != 1|| input[0]<'1'|| input[0]>'7'){
                fprintf(stderr, "Please only choose one number from 1 to 7.");
                continue;
            }
            cmd = atoi(input);
        }
        else{
            fprintf(stderr,"No input provided, the program is terminated.");
            exit(0);
        }

        //prevent operations until the database is imported
        if (cmd != 1 && DatabaseImported == 0){
            printf("Please import the Database first (Option 1).\n");
            continue;
        }

        if (cmd == 1){

            char filename[FILENAME_LEN];
            printf("Enter the filename to be imported: \n");
            if (fgets(filename, sizeof(filename), stdin) != NULL){
                printf("Did it go here?");
                filename[strcspn(filename, "\n")] = '\0';
/*
                for (int i=0; i<FILENAME_LEN; i++){
                    if (filename[i] == '\n'){
                        filename[i] = '\0';
                        break;
                    }
                }*/
                printf("or here?");
                importDB(filename);
                DatabaseImported = 1; //Update when database is imported sucessfully
                printf("File %s has been imported.\n", filename);
            }
            else {
                exit(0);
            }
        }
        
        /*else if (cmd == 2){
            char filename[FILENAME_LEN];
            printf("Enter the filename to be imported: ");
            if (fgets(filename, FILENAME_LEN, stdin) != NULL){
                exportDB(filename);
                printf("File %s has been exported", filename);

            }
            else {
                exit(0);
            }
        }
        */

        /*
        else if(cmd == 3){
            countEntriesOptions();
        }

        else if (cmd ==4){
            char* memberName = memberNameforSortbyMember();
            sortByMember (memberName);
        }

        else if (cmd == 5){
            editEntryOptions();
        }

        else if (cmd==6){
            sortByOptions();
        }
        */
    }
    return 0;

}


/*********************************************************************
Author: Helen Ly
Purpose: displaying menu for memberName options, get user input for searchValue
         and call countEntries() function using memberName and seachValue
Arguments: void
Returns: void
**********************************************************************/
/*void countEntriesOptions(){

    char* memberName = memberNameforCountEntries();

    if (memberName == NULL){
        fprintf(stderr, "No valid member name selected. Back to main menu.");
        return;
    }

    char searchValue[MAX_LEN];
    printf("Enter the value to be searched: ");
    fgets(searchValue, MAX_LEN, stdin);
    for (int i=0; i<MAX_LEN; i++){
        if (searchValue[i] == '\n'){ 
            searchValue[i] = '\0';
        }
    }
    int count = countEntries(memberName, searchValue);
    printf("There are %d entries of %s.\n", count, searchValue);

}
*/



/*********************************************************************
Author: Helen Ly
Purpose: get user input for report type options, then generate requested report
Arguments: void
Returns: void
**********************************************************************/
/*void sortByOptions(){

    //display menu by looping through the report type options
    char* options[2] = {"Report By Ward", "Report By Neighborhood ID"};
    printf("Select the Report Type: \n");
    for (int i =0; i<2;i++){
        printf("%d. %s", i+1, options[i]);
    }


    int select;
    //if user input NULL or more than a number, print error message

    if (scanf ("%d", &select) !=1){
        printf ("The selection is invalid. Choose 1 or 2 for available report type.\n");
    }
    
    //Otherwise, call the coresponding report as per user input
    if (select == 1){
        reportByWard();
    }
    else if (select == 2){
        reportByNeighbourhood();
    }
    else{
        printf ("Selection is invalid. Only choose 1 or 2.\n");
    }
}*/

/*********************************************************************
Author: Helen Ly
Purpose: get user input for tableID, memberName and newValue as input
         argument to call editTableEntry() function
Arguments: void
Returns: void
**********************************************************************/
/*
void editEntryOptions(){

    char tableID[INPUT_LEN];
    printf("Enter table ID: ");
    fgets(tableID, INPUT_LEN, stdin);
    for (int i=0; i<INPUT_LEN; i++){
        if (tableID[i] == '\n'){ 
            tableID[i] = '\0';
        }
    }

    char* memberName = memberNameforEditEntryOptions();
    if (memberName == NULL){
        fprintf(stderr, "No valid member name selected. Back to main menu.\n");
        return ;
    }

    char newValue[MAX_LEN];
    printf("Enter the new value: ");
    fgets(newValue, MAX_LEN, stdin);

    //remove newline char
    for (int i=0; i<MAX_LEN; i++){
        if (newValue[i] == '\n'){ 
            newValue[i] = '\0';
        }
    }

    editTableEntry(atoi(tableID), memberName, newValue);

}
    */