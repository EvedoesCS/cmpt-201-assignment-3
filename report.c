/******************************************************************
 Author: Ethan Collier
 Purpose: It counts the number of entries in the PicnicTable that match
 a specific memberName and value within Db
 Arguments:
    char* memberName -> Name of the member to search for (e.g., "Ward",
    "Table Type");
    char* value -> The value to match the entries against for the memberName;
 Returns: The number of entries that match the given memberName and value.
 *******************************************************************/
 int countEntries(char *memberName, char *value) {
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return 0;
    }

    int count = 0;
    struct pTableEntry *current = Db->picnicTableTable->head; 

    while (current) {
        if (strcmp(memberName, "Table Type") == 0 && 
            strcmp(Db->tableTypeTable->data[current->tableTypeIdx], value) == 0) { //It uses strcmp to check for matches based on the memberName and value
            count++;
        } else if (strcmp(memberName, "Surface Material") == 0 &&
                   strcmp(Db->surfaceMaterialTable->data[current->surfaceMatIdx], value) == 0) {
            count++;
        } else if (strcmp(memberName, "Structural Material") == 0 &&
                   strcmp(Db->structuralMaterialTable->data[current->structuralMatIdx], value) == 0) {
            count++;
        } else if (strcmp(memberName, "Neighborhood Name") == 0 &&
                   current->neighbourhoodId && strcmp(current->neighbourhoodId->value, value) == 0) {
            count++;
        } else if (strcmp(memberName, "Ward") == 0 &&
                   strcmp(current->ward, value) == 0) {
            count++;
        }
        current = current->next;
    }

    return count;
}
/******************************************************************
Author: Ethan Collier
Purpose: It sorts the PicnicTable within Db by the
values of the specified memberName in ascending order. "Ward" will
be sorted numerically, while others will be sorted alphabetically
Arguments:
   char* memberName -> Name of the member to sort by (e.g., "Ward",
   "Table Type", "Neighbourhood Name");
Returns: void
*******************************************************************/
void sortByMember(char *memberName) {
   if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
       printf("Error: Database is not initialized or empty.\n");
       return;
   }

   int size = Db->picnicTableTable->size;
   
   struct pTableEntry **array = malloc(size * sizeof(struct pTableEntry *)); //This creates an array that'll be used for sorting
   if (!array) {
       printf("Error: Memory allocation failed.\n");
       return;
   }

   struct pTableEntry *current = Db->picnicTableTable->head; 
   for (int i = 0; i < size; i++) {
       array[i] = current;
       current = current->next;
   }

   int (*compare)(const void *, const void *) = NULL;

   if (strcmp(memberName, "Table Type") == 0) { 
       compare = cmpTableType; //Calls the comparison functions from DB_impl
   } else if (strcmp(memberName, "Surface Material") == 0) {
       compare = cmpSurfaceMaterial;
   } else if (strcmp(memberName, "Structural Material") == 0) {
       compare = cmpStructuralMaterial;
   } else if (strcmp(memberName, "Neighbourhood Name") == 0) {
       compare = cmpNeighborhoodName;
   } else if (strcmp(memberName, "Ward") == 0) {
       compare = cmpWard;
   }

   if (!compare) {
       printf("Error: Unknown member name '%s'.\n", memberName);
       free(array);
       return;
   }

   qsort(array, size, sizeof(struct pTableEntry *), compare);

   Db->picnicTableTable->head = array[0]; //It constructs the linked list from the sorted array
   current = Db->picnicTableTable->head;
   for (int i = 1; i < size; i++) {
       current->next = array[i];
       current = current->next;
   }
   current->next = NULL;

   free(array);

   printf("Successfully sorted by %s.\n", memberName);
}
/******************************************************************
Author: Ethan Collier;
Purpose: It prints a listing of PicnicTable entries grouped by wards
in ascending numerical order from Db
Arguments: None
Returns: void
*******************************************************************/
void reportByWard() {
   sortByMember("Ward");
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return;
    }

    struct pTableEntry *current = Db->picnicTableTable->head;

    printf("\n--- Report by Ward ---\n");
    while (current != NULL) {
        printf("Ward: %s\n ID: %s\n Table Type: %s\n Surface Material: %s\n Structural Material: %s\n Street: %s\n Neighbourhood Name: %s\n Latitude: %s\n Longitude: %s\n\n",
               current->ward,
               current->id,
               Db->tableTypeTable->data[current->tableTypeIdx],
               Db->surfaceMaterialTable->data[current->surfaceMatIdx],
               Db->structuralMaterialTable->data[current->structuralMatIdx],
               current->street_ave,
               current->neighbourhoodId->value,
               current->latitude,
               current->longitude);
        current = current->next;
    }
}
/******************************************************************
Author: Ethan Collier
Purpose: It prints a listing of PicnicTable entries grouped by neighbourhoods
in ascending alphabetical order from Db
Arguments: None
Returns: void
*******************************************************************/
void reportByNeighbourhood() {
   sortByMember("Neighbourhood Name");
    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return;
    }
    struct pTableEntry *current = Db->picnicTableTable->head;

    printf("\n--- Report by Neighbourhood ---\n");
    while (current != NULL) {
        printf("Neighbourhood Name: %s\n ID: %s\n Table Type: %s\n Surface Material: %s\n Structural Material: %s\n Street: %s\n Ward: %s\n Latitude: %s\n Longitude: %s\n\n",
               current->neighbourhoodId->value,
               current->id,
               Db->tableTypeTable->data[current->tableTypeIdx],
               Db->surfaceMaterialTable->data[current->surfaceMatIdx],
               Db->structuralMaterialTable->data[current->structuralMatIdx],
               current->street_ave,
               current->ward,
               current->latitude,
               current->longitude);
        current = current->next;
    }
}

/*void print_db() { //THIS IS FOR TEMPORARY TESTING. REMOVE AFTER


    if (!Db || !Db->picnicTableTable || !Db->picnicTableTable->head) {
        printf("Error: Database is not initialized or empty.\n");
        return;
    }
    struct pTableEntry *current = Db->picnicTableTable->head;


    while (current != NULL) {
        printf("\nTable ID: %d\nNeighbourhood Name: %s\nID: %s\nTable Type: %s\nSurface Material: %s\nStructural Material: %s\n"
            "Street: %s\nWard: %s\nLatitude: %s\nLongitude: %s\n",
            current->tableId,
            current->neighbourhoodId->value,
            current->id,
            Db->tableTypeTable->data[current->tableTypeIdx],
            Db->surfaceMaterialTable->data[current->surfaceMatIdx],
            Db->structuralMaterialTable->data[current->structuralMatIdx],
            current->street_ave,
            current->ward,
            current->latitude,
            current->longitude);
        printf("----------------------------------\n");
        current = current->next;
    }

}*/

/*int main() {
     db_create();
     printf("Database initialized successfully.\n");
 
     char *filename = "./src/backend/dataset/PicnicTableSmall.csv"; 
     importDB(filename);
     printf("Data imported successfully from %s.\n", filename);
     int choice;
 
     while (1) {
         printf("\n--- Picnic Table Management System ---\n");
         printf("1. Count Entries\n");
         printf("2. Sort Entries by Member\n");
         printf("3. Report by Ward\n");
         printf("4. Report by Neighbourhood\n");
         printf("5. Exit\n");
         printf("6. Print all\n");
         printf("Enter your choice: ");
         scanf("%d", &choice);
         getchar(); 
 
         switch (choice) {
             case 1: 
                 printf("Enter the member to count (e.g., 'Ward', 'Table Type', 'Neighborhood Name'): ");
                 char memberName[MAX_SIZE];
                 fgets(memberName, sizeof(memberName), stdin);
                 memberName[strcspn(memberName, "\n")] = '\0';
 
                 printf("Enter the value to count: ");
                 char value[MAX_SIZE];
                 fgets(value, sizeof(value), stdin);
                 value[strcspn(value, "\n")] = '\0';
 
                 int result = countEntries(memberName, value);
                 printf("Number of entries for %s = %s: %d\n", memberName, value, result);
                 break;
 
             case 2: 
                 printf("Enter the member to sort by (e.g., 'Ward', 'Table Type', 'Neighborhood Name'): ");
                 fgets(memberName, sizeof(memberName), stdin);
                 memberName[strcspn(memberName, "\n")] = '\0';
 
                 sortByMember(memberName);
                 printf("Sorted entries by %s.\n", memberName);
                 break;
 
             case 3: 
                 reportByWard();
                 break;
 
             case 4: 
                 reportByNeighbourhood();
                 break;
 
             case 5: 
                 printf("Freeing database and exiting...\n");
                 printf("Goodbye!\n");
                 return 0;
            case 6:
                print_db();
 
             default:
                 printf("Invalid choice. Please try again.\n");
         }
     }
 }*/


 //DB_impl.c below

 //This is a comparison function tht compares table type entries
 int cmpTableType(const void *a, const void *b) {
    struct pTableEntry *entryA = *(struct pTableEntry **)a; //It defereneces and gets the entry
    struct pTableEntry *entryB = *(struct pTableEntry **)b;
    return strcmp(Db->tableTypeTable->data[entryA->tableTypeIdx], Db->tableTypeTable->data[entryB->tableTypeIdx]);
}
//This is a comparison function tht compares surface material entries
int cmpSurfaceMaterial(const void *a, const void *b) {
    struct pTableEntry *entryA = *(struct pTableEntry **)a;
    struct pTableEntry *entryB = *(struct pTableEntry **)b;
    return strcmp(Db->surfaceMaterialTable->data[entryA->surfaceMatIdx], Db->surfaceMaterialTable->data[entryB->surfaceMatIdx]);
}
//This is a comparison function tht compares structural material entries
int cmpStructuralMaterial(const void *a, const void *b) {
    struct pTableEntry *entryA = *(struct pTableEntry **)a;
    struct pTableEntry *entryB = *(struct pTableEntry **)b;
    return strcmp(Db->structuralMaterialTable->data[entryA->structuralMatIdx], Db->structuralMaterialTable->data[entryB->structuralMatIdx]);
}
//This is a comparison function tht compares neighborhood name entries
int cmpNeighborhoodName(const void *a, const void *b) {
    struct pTableEntry *entryA = *(struct pTableEntry **)a;
    struct pTableEntry *entryB = *(struct pTableEntry **)b;
    if (entryA->neighbourhoodId && entryB->neighbourhoodId) {
        return strcmp(entryA->neighbourhoodId->value, entryB->neighbourhoodId->value);
    }
    return 0;
}
//This is a comparison function tht compares ward entries, uses atoi to find the number in the string
int cmpWard(const void *a, const void *b) {
    struct pTableEntry *entryA = *(struct pTableEntry **)a;
    struct pTableEntry *entryB = *(struct pTableEntry **)b;
    int wardA = atoi(entryA->ward + 5); //Uses atoi to read the number in the string, and skips the first five characters in the string (WARD )
    int wardB = atoi(entryB->ward + 5);
    return wardA - wardB;
}