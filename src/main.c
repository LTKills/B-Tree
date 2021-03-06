/*Files Organization Project Part 2*/
// Class A
// Group Number 12

/*==================Students==================*/

// Gabriel de Melo Cruz     9763043
// Bruno Gomes Coelho       9791160
// Marcello Pagano          9791031

/*============================================*/

#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <insertion.h>
#include <remotion.h>
#include <search.h>
#include <statistics.h>


// Prints menu for choosing main operation
int print_main_menu() {
    char *string = NULL;
    int option = INVALID;

    while((option > 5) || (option < 1)) {
        printf("\n\n\n");
        printf("==================MENU==================\n");
        printf("=                                      =\n");
        printf("= 1. Insert record.                    =\n");
        printf("= 2. Remove record.                    =\n");
        printf("= 3. Statistics about index files.     =\n");
        printf("= 4. Statistics about removed records. =\n");
        printf("= 5. Exit.                             =\n");
        printf("=                                      =\n");
        printf("========================================\n");
        printf("\n\n");
        string = read_line(stdin, '\n', '\n', VARIABLE_FIELD);
        option = atoi(string);
        free(string);
    }

    return option;
}


/*Calls funtions and performs desired operation*/
int choose_operation(int option, t_files *files, t_list *lists) {
    switch(option) {
        case EXIT:
            return STOP;

        case INSERTION:
            insert(files, lists);
            break;

        case REMOTION:
        	fseek(files->outputBest, 0, SEEK_SET);
            remove_record(files, lists);
            break;

        case INDEX_STATISTICS:
            index_stats(files, lists);
            break;

        case REMOVED_STATISTICS:
            removed_stats(files, lists);
            break;

    }

    return GO;
}


int main(int argc, char *argv[]) {
    FILE *input;
    t_list *lists;
    int option = INVALID, stat = GO;

    // Treat not-enough-arguments case
    if(argc != NARGS) {
        printf("Wrong usage.\n");
        printf("usage: ./binary_name input_file\n");
        printf("Terminating\n");
        return 1;
    }

    input = fopen(argv[INPUTFILE], "r");

    // Read input file and create output and index files
    // utils.h
    t_files *files = initialize(input);

    lists = create_index_lists();

    // Execute until stop is required
    while(stat != STOP) {
        option = print_main_menu();
        stat = choose_operation(option, files, lists);
    }


    // Close all files' descriptors
    // utils.h
    close_files(input, files);

    free(files);
    free(lists);

    return 0;
}
