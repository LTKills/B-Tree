#include <stdlib.h>
#include <stdio.h>
#include <utils.h>


void initialize(FILE *input, FILE **outputBest, FILE **indexBest,
    FILE **outputWorst, FILE **indexWorst, FILE **outputFirst, FILE **indexFirst) {

    *outputBest = fopen("best.dat", "wb");
    *indexBest = fopen("best.idx", "wb");

    *outputWorst = fopen("worst.dat", "wb");
    *indexWorst = fopen("worst.idx", "wb");

    *outputFirst = fopen("first.dat", "wb");
    *indexFirst = fopen("first.idx", "wb");
}



void close_files(FILE *input, FILE *outputBest, FILE *indexBest,
    FILE *outputWorst, FILE *indexWorst, FILE *outputFirst, FILE *indexFirst) {

    fclose(input);

    fclose(outputBest);
    fclose(indexBest);

    fclose(outputWorst);
    fclose(indexWorst);

    fclose(outputFirst);
    fclose(indexFirst);
}
