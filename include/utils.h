/*================================Utils================================*/
// Author: Cruz

// This file holds important structs, defines and enums
// as well as useful functions that we didn't  know where to put

/*=====================================================================*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>

#define FIELD_DELIM ';'
#define FIXED_SIZE 20
#define LINE_END '\n'

/*Main function arguments*/
enum ARGS {
    PROGNAME,
    INPUTFILE,
    NARGS
};


/*Main menu options*/
enum MAIN_OPTIONS {
    ZERO,
    INSERTION,
    REMOTION,
    INDEX_STATISTICS,
    REMOVED_STATISTICS,
    EXIT,
    NOPTIONS
};


enum FIELD_TYPE {
    FIXED_FIELD,
    VARIABLE_FIELD
};

/*Stop conditions*/
enum STATS {
    STOP,
    GO,
};


/*File Structure*/
typedef struct {
    unsigned int ticket;
    /*These have FIXED_SIZE == 20*/
    char *documento, *dataHoraCadastro, *dataHoraAtualiza;

    /*These have variable size*/
    char *dominio, *nome, *cidade, *uf;
} t_record;


/*========== FUNCTIONS ==========*/

void free_record(t_record *record);


void print_record(t_record *record);


void swap(int **vec, int a, int b);


void read_input_record(FILE *input, t_record *record);


char *read_line(FILE *stream, char delim, char lineEnd, int fieldType);


void read_input(FILE *input, FILE *output, FILE *index);


void initialize(FILE *input, FILE **outputBest, FILE **indexBest,
    FILE **outputWorst, FILE **indexWorst, FILE **outputFirst, FILE **indexFirst);


void close_files(FILE *input, FILE *outputBest, FILE *indexBest,
    FILE *outputWorst, FILE *indexWorst, FILE *outputFirst, FILE *indexFirst);


#endif
