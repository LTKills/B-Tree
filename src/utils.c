#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <quick.h>


/*Print record for testing purposes*/
void print_record(t_record *record) {
    printf("Dominio: %s\n", record->dominio);
    printf("Documento: %s\n", record->documento);
    printf("Nome: %s\n", record->nome);
    printf("UF: %s\n", record->uf);
    printf("Cidade: %s\n", record->cidade);
    printf("DataHoraCadastro: %s\n", record->dataHoraCadastro);
    printf("DataHoraAtualiza: %s\n", record->dataHoraCadastro);
    printf("Ticket: %d\n", record->ticket);
}


/*Swap function for quickSort*/
void swap(int **vec, int a, int b) {
    int aux1 = vec[0][a];
    int aux2 = vec[1][a];

    vec[0][a] = vec[0][b];
    vec[1][a] = vec[1][b];

    vec[0][b] = aux1;
    vec[1][b] = aux2;
}



/*Reads one line of input file until '\n' or delim*/
char *read_line(FILE *stream, char delim, char lineEnd, int fieldType) {
    int i = 0, reallocCount = 0; //reallocCount guarda a qtd de reallocs ja feitos
    char letter, *string;
    string = (char *) malloc(50 * sizeof(char));
    letter = fgetc(stream);


    while (letter != delim && letter != lineEnd && letter != EOF) {
        string[i] = letter;
        i++;
        letter = fgetc(stream);
        if (i >= 50*(reallocCount +1)) {
            string = (char *) realloc(string, 50 * (reallocCount +2)*sizeof(char));
            reallocCount++;
        }
    }
    string = realloc(string, (i+1)*sizeof(char));
    string[i++] = '\0';

    // Fixes size of the field if it is a FIXED_SIZE field
    if(fieldType == FIXED_FIELD){
        string = realloc(string, sizeof(char)*FIXED_SIZE);
        while(i < FIXED_SIZE) {
            string[i++] = 0;
        }
    }
    return string;
}


/*Reads an record from input file*/
void read_input_record(FILE *input, t_record *record) {
    char *temp;

    record->dominio = read_line(input, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->documento = read_line(input, FIELD_DELIM, LINE_END, FIXED_FIELD);
    record->nome = read_line(input, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->uf = read_line(input, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->cidade = read_line(input, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->dataHoraCadastro = read_line(input, FIELD_DELIM, LINE_END, FIXED_FIELD);
    record->dataHoraAtualiza = read_line(input, FIELD_DELIM, LINE_END, FIXED_FIELD);
    temp = read_line(input, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->ticket = atoi(temp);

    free(temp);
}


/*Jumps to next record suposing that the ticket field has been read*/
void get_next_record(FILE *output) {
    int size = 0, i;
    char test = 'a';


    fseek(output, 3*FIXED_SIZE, SEEK_CUR); // jumps fixed sized fields

    for(i = 0; i < 4; i++) {
        fread(&size, sizeof(int), 1, output); // read size indicator
        fseek(output, size, SEEK_CUR);        // jump field
    }

    fread(&test, sizeof(char), 1, output);
}


/*Writes the record into the output file*/
void write_output_record(FILE *output, t_record *record) {
    int sizeIndicator = 0;
    char recordDelim = '#';

    // Write fixed size fields
    fwrite(&record->ticket, sizeof(int), 1, output);
    fwrite(record->documento, sizeof(char), FIXED_SIZE, output);
    fwrite(record->dataHoraCadastro, sizeof(char), FIXED_SIZE, output);
    fwrite(record->dataHoraAtualiza, sizeof(char), FIXED_SIZE, output);

    // Write variable sized fields with size indicators
    sizeIndicator = strlen(record->dominio)+1;
    fwrite(&sizeIndicator, sizeof(int), 1, output);
    fwrite(record->dominio, sizeof(char), strlen(record->dominio)+1, output);

    sizeIndicator = strlen(record->nome)+1;
    fwrite(&sizeIndicator, sizeof(int), 1, output);
    fwrite(record->nome, sizeof(char), strlen(record->nome)+1, output);

    sizeIndicator = strlen(record->uf)+1;
    fwrite(&sizeIndicator, sizeof(int), 1, output);
    fwrite(record->uf, sizeof(char), strlen(record->uf)+1, output);

    sizeIndicator = strlen(record->cidade)+1;
    fwrite(&sizeIndicator, sizeof(int), 1, output);
    fwrite(record->cidade, sizeof(char), strlen(record->cidade)+1, output);

    fwrite(&recordDelim, sizeof(char), 1, output);
}


/*Frees all the varible sized fields of the record*/
void free_record(t_record *record) {
    free(record->documento);
    free(record->dataHoraCadastro);
    free(record->dataHoraAtualiza);
    free(record->dominio);
    free(record->nome);
    free(record->cidade);
    free(record->uf);

    free(record);
}


/*Uses the ticket to create the index file*/
void create_index_file(FILE *output, FILE *index) {
    int **tickets = calloc(2, sizeof(int*)), n = 0;

    fseek(output, 0, SEEK_SET);
    fseek(index, 0, SEEK_SET);

    while(!feof(output)) {
        tickets[0] = realloc(tickets[0], sizeof(int) * (n+1));
        tickets[1] = realloc(tickets[1], sizeof(int) * (n+1));

        tickets[1][n] = ftell(output);
        fread(&tickets[0][n++], sizeof(int), 1, output);

        if(feof(output)) break;

        get_next_record(output);
    }

    quickSort(tickets, 0, n-2);

    fwrite(tickets[0], sizeof(int), n-1, index);
    fwrite(tickets[1], sizeof(int), n-1, index);

    free(tickets[0]);
    free(tickets[1]);
    free(tickets);
}



/*Reads input file and creates index and output files*/
void read_input(FILE *input, FILE *output, FILE *index) {
    t_record *record;

    fseek(input, 0, SEEK_SET);

    // Creating output file
    while(!feof(input)) {
        record = malloc(sizeof(t_record));
        read_input_record(input, record);

        if(feof(input)) {
            free_record(record);
            break;
        }

        write_output_record(output, record);

        free_record(record);

    }

    // Create index from output generated above
    create_index_file(output, index);

}


t_list *create_index_lists() {
	int i;
	t_list *lists = malloc(3*sizeof(t_list));
	for (i = 0; i < 3; i += 1) {
		lists[i].head = INVALID;
		lists[i].removed = 0;
	}
	return lists;
}



/*Reads input file and generates index and output files*/
t_files *initialize(FILE *input) {
	t_files *files = malloc(sizeof(t_files));

    files->outputBest = fopen("best.dat", "w+");
    files->indexBest = fopen("best.idx", "w+");
    read_input(input, files->outputBest, files->indexBest);

    files->outputWorst = fopen("worst.dat", "w+");
    files->indexWorst = fopen("worst.idx", "w+");
    read_input(input, files->outputWorst, files->indexWorst);

    files->outputFirst = fopen("first.dat", "w+");
    files->indexFirst = fopen("first.idx", "w+");
    read_input(input, files->outputFirst, files->indexFirst);

	return files;
}



/* Returns the next element in the linked list.
If the element is not invalid, also return by nextSize its size. */
int next_element(FILE *fp, int byteOffset, int *nextSize) {
	int next;
	
	fseek(fp, byteOffset, SEEK_SET); // Go to the current position 
	fseek(fp, 2*sizeof(int), SEEK_CUR); // skip over invalid and reg size
	
	fread(&next, sizeof(int), 1, fp); // gets the next element in the linked list
	
	fseek(fp, next, SEEK_SET); // Go to the next element
	fseek(fp, sizeof(int), SEEK_CUR); // skip over invalid 
	fread(nextSize, sizeof(int), 1, fp); // reads the size of the next element
	
	return next;
}


/* Gets the size of a given register that starts at byteOffset */
int get_register_size(FILE *fp, int byteOffset) {
	char aux = 'a';
	int counter = 0;

	// Go to 'byteOffset'
	fseek(fp, byteOffset, SEEK_SET);

	// Go to the end of the record to count it's size
	while (!feof(fp) && aux != '#') {
		fread(&aux, sizeof(char), 1, fp);
		if (!feof(fp)) counter++;
	}
	
	//TODO: debugging only
	if (counter == 0)
		printf("GEEEEEEEEEEEEEEEEEEEEEEEEENTE DEU RUIM, UTILS.C, GET_REGISTER_SIZE");
	
	
	return counter;
	
}



/* Gets the size of a given file */
int get_file_size(FILE *file) {
	int byteOffset;
	fseek(file, 0, SEEK_END); // Go to the end of the file
	byteOffset = ftell(file); // Get its size
	rewind(file);
	return byteOffset;
}


/*Closes files' descriptors*/
void close_files(FILE *input, t_files *files) {

    fclose(input);

    fclose(files->outputBest);
    fclose(files->indexBest);

    fclose(files->outputWorst);
    fclose(files->indexWorst);

    fclose(files->outputFirst);
    fclose(files->indexFirst);
}
