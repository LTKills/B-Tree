/*================================Utils================================*/
// Author: Cruz

// This file holds important structs, defines and enums
// as well as useful functions that actually we didn't
// know where to put

/*=====================================================================*/

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

enum {
    STOP,
    GO,
};


void initialize(FILE *input, FILE **outputBest, FILE **indexBest,
    FILE **outputWorst, FILE **indexWorst, FILE **outputFirst, FILE **indexFirst);

void close_files(FILE *input, FILE *outputBest, FILE *indexBest,
    FILE *outputWorst, FILE *indexWorst, FILE *outputFirst, FILE *indexFirst);
