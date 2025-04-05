/***************************countEntries**********************************
Author: Ethan Collier
Purpose: It counts how many entries match a specific memberName and value in the picnicTable
Arguments:
    memberName -> Name of the member to match (e.g., "Ward", "Table Type", "Neighbourhood Name").
    value -> The value to count occurrences of for the given memberName.
Returns: The number of entries that match the specified memberName and value.
**********************************************************************/
int countEntries(char *memberName, char *value);

/***************************sortByMember**********************************
Author: Ethan Collier
Purpose: It sorts the picnicTable by the values of the specified memberName in order
Arguments:
    memberName -> Name of the member to sort by (e.g., "Ward", "Table Type").
Returns: void
**********************************************************************/
void sortByMember(char *memberName);

/***************************reportByNeighbourhood**********************************
Author: Ethan Collier
Purpose: It prints the list of picnic tables grouped by neighborhoods in alphabetical order
Arguments: None
Returns: void
**********************************************************************/
void reportByNeighbourhood();

/***************************reportByWard**********************************
Author: Ethan Collier
Purpose: It prints the list of picnic tables grouped by wards in ascending numerical order
Arguments: None
Returns: void
**********************************************************************/
void reportByWard();


//DB_impl.h below


int cmpTableType(const void *a, const void *b);

int cmpSurfaceMaterial(const void *a, const void *b);

int cmpStructuralMaterial(const void *a, const void *b);

int cmpNeighborhoodName(const void *a, const void *b);

int cmpWard(const void *a, const void *b);