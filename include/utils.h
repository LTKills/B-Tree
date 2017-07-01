/*================================Utils================================*/
// Author: Cruz

// This file holds important structs, defines and enums
// as well as useful functions that we didn't  know where to put TODO: não gostei dessa coisa de não sabermos onde colocar

/*=====================================================================*/

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

void swap(int **vec, int a, int b);

char *read_line(FILE *stream, char delim, char lineEnd, int fieldType);

void read_input(FILE *input, FILE *output, FILE *index);

void initialize(FILE *input, FILE **outputBest, FILE **indexBest,
    FILE **outputWorst, FILE **indexWorst, FILE **outputFirst, FILE **indexFirst);


void close_files(FILE *input, FILE *outputBest, FILE *indexBest,
    FILE *outputWorst, FILE *indexWorst, FILE *outputFirst, FILE *indexFirst);
