


// Sort entries by member
void sortByMemberMenu() {
    char memberName[MAX_BUFFER];
    printf("Enter member name to sort by: ");
    fgets(memberName, MAX_BUFFER, stdin);
    memberName[strcspn(memberName, "\n")] = 0;

    sortByMember(memberName);
    printf("Entries sorted by %s.\n", memberName);
}



// Edit an entry
void editEntryMenu() {
    int tableID;
    char memberName[MAX_BUFFER], newValue[MAX_BUFFER];

    printf("Enter table ID: ");
    if (scanf("%d", &tableID) != 1) {
        printf("Invalid table ID.\n");
        while (getchar() != '\n'); // Clear invalid input
        return;
    }
    getchar(); // Clear newline

    printf("Enter member name to edit: ");
    fgets(memberName, MAX_BUFFER, stdin);
    memberName[strcspn(memberName, "\n")] = 0;

    printf("Enter new value: ");
    fgets(newValue, MAX_BUFFER, stdin);
    newValue[strcspn(newValue, "\n")] = 0;

    char *data[3] = {memberName, newValue, NULL};
    char *result[1] = {NULL};

    db_query("UPDATE", data, 2, "picnicTableTable", NULL, result);
    printf("Entry updated successfully.\n");
}

// Generate report by ward or neighborhood
void reportMenu() {
    int reportType;
    printf("Choose report type:\n");
    printf("1. Report by Neighbourhood\n");
    printf("2. Report by Ward\n");
    if (scanf("%d", &reportType) != 1) {
        printf("Invalid choice.\n");
        while (getchar() != '\n'); // Clear invalid input
        return;
    }
    getchar(); // Clear newline

    if (reportType == 1) {
        reportByNeighbourhood();
    } else if (reportType == 2) {
        reportByWard();
    } else {
        printf("Invalid choice.\n");
    }
}

// Run tests for import.c
void runTests() {
    printf("Running Import Tests...\n");
    if (test_prompt_file_path() == 0 &&
        test_tokenize_string() == 0 &&
        test_load_from_file() == 0) {
        printf("\nAll import tests passed successfully!\n");
    } else {
        printf("\nSome import tests failed. Check your code.\n");
    }
}
