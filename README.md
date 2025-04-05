# cmpt-201-assignment-3
The code for our cmpt assignment 3

FILE CONTENTS:
    dashboard.c -> The location of the main function.
    and helper function to display parts of the UI.
    DB.h -> contains main function prototypes.
    DB_impl.h -> contains helper function prototypes.
    DB.c -> Contains main function logic.
    DB_impl.c -> contains the logic for helper functions
    used in DB.c.
    makefile -> makefile for the program. The target "dashboard" is
    used to output the executable file "dashboard" which can be 
    run to use our program.


TESTING: 
We use valgrind, gdb, manual testing to determine if the program was
working properly. We believe this is more than sufficent to test our
program. Valgrind reported no memory leaks and all functions seem to 
be outputing the expected results.
