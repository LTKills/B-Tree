#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <utils.h>
#include <statistics.h>




/*Displays menu for showing index statistics*/
int print_index_stats_menu(int nfirst, int nworst, int nbest,
        int **first, int **best, int **worst, int counter) {

        char *string = NULL, next[2] = {'n', '\0'};
        int op = STOP;


        printf("\n\n\n");
        printf("=================================INDEX=STATISTICS=================================\n");
        printf("                        Best-Fit\tWorst-Fit\tFirst-Fit\n");
        printf("                                                                                  \n");
        printf(" Number of Records         %d\t\t%d\t\t%d\n", nbest, nworst, nfirst);
        printf("                                                                                  \n");
        printf(" Entry (Ticket)            %d\t\t%d\t\t%d\n", best[0][counter], worst[0][counter], first[0][counter]);
        printf("                                                                                  \n");
        printf(" Byte Offset               %d\t\t%d\t\t%d\n", best[1][counter], worst[1][counter], first[1][counter]);
        printf("                                                                                  \n");
        printf("     Next(n)                                                   Exit(any key)      \n");
        printf("==================================================================================\n");
        printf("\n\n");
        string = read_line(stdin, '\n', '\n', VARIABLE_FIELD);

        if(strcmp(string, next) == 0) op = GO;

        free(string);
        return op;
}


/*Statistics about the index files*/
void index_stats(t_files *files, t_list *lists) {
    int **first = calloc(2, sizeof(int*)),
        **best = calloc(2, sizeof(int*)),
        **worst = calloc(2, sizeof(int*));

    int nfirst = 0, nbest = 0, nworst = 0, i, op = STOP;



    /*Go to end of file and figure how many integers there are*/
    fseek(files->indexFirst, 0, SEEK_END);
    nfirst = ftell(files->indexFirst)/sizeof(int);

    fseek(files->indexWorst, 0, SEEK_END);
    nworst = ftell(files->indexWorst)/sizeof(int);

    fseek(files->indexBest, 0, SEEK_END);
    nbest = ftell(files->indexBest)/sizeof(int);



    /*Go back to beginning of the files and read the data*/
    fseek(files->indexFirst, 0, SEEK_SET);
    fseek(files->indexWorst, 0, SEEK_SET);
    fseek(files->indexBest, 0, SEEK_SET);

    first[0] = malloc(sizeof(int)*nfirst/2);
    first[1] = malloc(sizeof(int)*nfirst/2);

    worst[0] = malloc(sizeof(int)*nworst/2);
    worst[1] = malloc(sizeof(int)*nworst/2);

    best[0] = malloc(sizeof(int)*nbest/2);
    best[1] = malloc(sizeof(int)*nbest/2);


    fread(first[0], sizeof(int), nfirst/2, files->indexFirst);
    fread(first[1], sizeof(int), nfirst/2, files->indexFirst);

    fread(worst[0], sizeof(int), nworst/2, files->indexWorst);
    fread(worst[1], sizeof(int), nworst/2, files->indexWorst);

    fread(best[0], sizeof(int), nbest/2, files->indexBest);
    fread(best[1], sizeof(int), nbest/2, files->indexBest);

    /*****************************************************/

    /*Present the data cutely*/
    i = 0;
    do {
        op = print_index_stats_menu(nfirst, nworst, nbest,
                first, best, worst, i);
        i++;
    } while(op == GO);



    /*Deallocate*/
    for(i = 0; i < 2; i++) {
        free(first[i]);
        free(best[i]);
        free(worst[i]);
    }

    free(first);
    free(best);
    free(worst);
}


/*Statistics about the removed records*/
void removed_stats(t_files *files, t_list *lists) {

}
