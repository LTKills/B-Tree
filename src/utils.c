#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>


/*Reads one line of input file until '\n' or delim*/
char *readLine(FILE *stream, char delim, char line_end) {
    int i = 0, realloc_count = 0; //realloc_count guarda a qtd de reallocs ja feitos
    char letter, *string;
    string = (char *) malloc(50 * sizeof(char));
    letter = fgetc(stream);


    while (letter != delim && letter != '\n' && letter != EOF) {
        string[i] = letter;
        i++;
        letter = fgetc(stream);
        if (i >= 50*(realloc_count +1)) {
            string = (char *) realloc(string, 50 * (realloc_count +2)*sizeof(char));
            realloc_count++;
        }
    }
    string = realloc(string, (i+1)*sizeof(char));
    string[i] = '\0';
    return string;
}


/*Reads an record from input file*/
void readInputRecord(FILE *input, t_record *record) {
    char *temp;

    record->dominio = readLine(input, FIELD_DELIM, LINE_END);
    record->documento = readLine(input, FIELD_DELIM, LINE_END);
    //printf("DOCUMENTO ABIGOS %s\n", record->documento);
    record->nome = readLine(input, FIELD_DELIM, LINE_END);
    record->uf = readLine(input, FIELD_DELIM, LINE_END);
    record->cidade = readLine(input, FIELD_DELIM, LINE_END);
    record->dataHoraCadastro = readLine(input, FIELD_DELIM, LINE_END);
    record->dataHoraAtualiza = readLine(input, FIELD_DELIM, LINE_END);
    temp = readLine(input, FIELD_DELIM, LINE_END);
    record->ticket = atoi(temp);

    //printf("=======================================================\n");
    //printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", record->dominio, record->documento, record->nome,
    //        record->uf, record->cidade, record->dataHoraCadastro, record->dataHoraAtualiza,
    //        record->ticket);

    free(temp);
}


/*Writes the record into the output file*/
void writeOutputRecord(FILE *output, t_record *record) {

    // Write fixed size fields
    fwrite(&record->ticket, sizeof(long long unsigned int), 1, output);
    fwrite(record->documento, sizeof(char), FIXED_SIZE, output);
    fwrite(record->dataHoraCadastro, sizeof(char), FIXED_SIZE, output);
    fwrite(record->dataHoraAtualiza, sizeof(char), FIXED_SIZE, output);

    // Write variable sized fields
    fwrite(record->dominio, sizeof(char), strlen(record->dominio)+1, output);
    fwrite(record->nome, sizeof(char), strlen(record->nome)+1, output);
    fwrite(record->uf, sizeof(char), strlen(record->uf)+1, output);
    fwrite(record->cidade, sizeof(char), strlen(record->cidade)+1, output);
}


/*Frees all the varible sized fields of the record*/
void freeRecord(t_record *record) {
    free(record->documento);
    free(record->dataHoraCadastro);
    free(record->dataHoraAtualiza);
    free(record->dominio);
    free(record->nome);
    free(record->cidade);
    free(record->uf);
}


/*Uses the ticket to create the index file*/
void createIndexFile(FILE *output, FILE *index) {
    // placeholder
}


/*Reads input file and creates index and output files*/
void readInput(FILE *input, FILE *output, FILE *index) {
    t_record *record = malloc(sizeof(t_record));

    // Creating output file
    while(!feof(input)) {
        readInputRecord(input, record);

        if(feof(input)) {
            freeRecord(record);
            free(record);
            break;
        }

        //writeOutputRecord(output, record);
        freeRecord(record);
    }

    // Create index from output generated above
    createIndexFile(output, index);

    free(record);
}


/*Reads input file and generates index and output files*/
void initialize(FILE *input, FILE **outputBest, FILE **indexBest,
    FILE **outputWorst, FILE **indexWorst, FILE **outputFirst, FILE **indexFirst) {

    *outputBest = fopen("best.dat", "wb");
    *indexBest = fopen("best.idx", "wb");
    readInput(input, *outputBest, *indexBest);

    *outputWorst = fopen("worst.dat", "wb");
    *indexWorst = fopen("worst.idx", "wb");
    readInput(input, *outputWorst, *indexWorst);

    *outputFirst = fopen("first.dat", "wb");
    *indexFirst = fopen("first.idx", "wb");
    readInput(input, *outputFirst, *indexFirst);
}


/*Closes files' descriptors*/
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
