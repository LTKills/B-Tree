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
    int option = -1;

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
        scanf("%d", &option);
    }

    return option;
}


/*Calls funtions and performs desired operation*/
int choose_operation(int option) {
    switch(option) {
        case EXIT:
            return STOP;

        case INSERTION:
            printf("placeholder for insert\n");
//            insert();
            break;

        case REMOTION:
            printf("placeholder for remove\n");
//            remove();
            break;

        case INDEX_STATISTICS:
            printf("placeholder for index stats\n");
//            index_stats();
            break;

        case REMOVED_STATISTICS:
            printf("placeholder for remove stats\n");
//            removed_stats();
            break;

        default:
            printf("Should never get here\n");
            return STOP;
    }

    return GO;
}


int main(int argc, char *argv[]) {
    FILE *input, *outputWorst, *outputBest, *outputFirst;
    FILE *indexWorst, *indexBest, *indexFirst;
    int option = -1, stat = GO;

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
    initialize(input, &outputBest, &indexBest,
        &outputWorst, &indexWorst, &outputFirst, &indexFirst);


    // Execute until stop is required
    while(stat != STOP) {
        option = print_main_menu();
        stat = choose_operation(option);
    }


    // Close all files' descriptors
    // utils.h
    close_files(input, outputBest, indexBest,
        outputWorst, indexWorst, outputFirst, indexFirst);


    return 0;
}
