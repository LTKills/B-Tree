/*Files Organization Project Part 2*/

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
int make_operation(int option) {
    switch(option) {
        case EXIT:
            printf("placeholder for exit\n");
            return STOP;

        case INSERTION:
            printf("placeholder for insert\n");
            break;

        case REMOTION:
            printf("placeholder for remove\n");
            break;

        case INDEX_STATISTICS:
            printf("placeholder for index stats\n");
            break;

        case REMOVED_STATISTICS:
            printf("placeholder for remove stats\n");
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
    int option = -1, stop = GO;

    // Treat not enough arguments case
    if(argc != NARGS) {
        printf("Wrong usage.\n");
        printf("usage: ./binary_name input_file\n");
        printf("Terminating\n");
        return 1;
    }

    input = fopen(argv[INPUTFILE], "r");

    // Read input file and create output and index files
    initialize(input, &outputBest, &indexBest,
        &outputWorst, &indexWorst, &outputFirst, &indexFirst);


    // Execute until stop is required
    while(stop != STOP) {
        option = print_main_menu();
        stop = make_operation(option);
    }


    close_files(input, outputBest, indexBest,
        outputWorst, indexWorst, outputFirst, indexFirst);


    return 0;
}
