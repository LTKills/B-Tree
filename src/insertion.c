#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <search.h>
#include <check.h>


/*Gets all the data for the new record*/
t_record *print_insert_menu() {
    t_record *record = malloc(sizeof(t_record));
    char *temp = NULL;

    printf("\n\nInsert field 'dominio': ");
    record->dominio = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);

    do {
         printf("Insert field 'documento': ");
         record->documento = read_line(stdin, FIELD_DELIM, LINE_END, FIXED_FIELD);
    } while(!checkInputDocument(record->documento));

    printf("Insert field 'nome': ");
    record->nome = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);

    printf("Insert field 'uf': ");
    record->uf = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);

    printf("Insert field 'cidade': ");
    record->cidade = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);

    do {
        printf("Insert field 'dataHoraCadastro': ");
        record->dataHoraCadastro = read_line(stdin, FIELD_DELIM, LINE_END, FIXED_FIELD);
    } while(!checkInputDateAndTime(record->dataHoraCadastro)); // test

    do {
        printf("Insert field 'dataHoraAtualiza': ");
        record->dataHoraAtualiza = read_line(stdin, FIELD_DELIM, LINE_END, FIXED_FIELD);
    } while(!checkInputDateAndTime(record->dataHoraAtualiza)); // test

    printf("Insert field 'ticket': ");
    temp = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
    record->ticket = atoi(temp);

    free(temp);

    // For debugging purposes
    // print_record(record);
    //
    printf("\n\n");

    return record;
}


/*Calculates size of the whole final record*/
int calculate_size(t_record *record) {
    int size = sizeof(int)*5; // size indicators + ticket(int)

    size += sizeof(char)*FIXED_SIZE*3; // fixed size

    // variable sized fields
    size += strlen(record->dominio) + 1;
    size += strlen(record->nome) + 1;
    size += strlen(record->uf) + 1;
    size += strlen(record->cidade) + 1;

    size += sizeof(char); // record delimiter
    return size;

}



void insert(t_files *files, t_list *lists) {
    t_record *record;
    int pos = -1, size;


    record = print_insert_menu();
    size = calculate_size(record);

    /*INSERT ON FIRST*/
    pos = search_insertion(files->outputFirst, lists, size);           // TODO: corrigir t_list
    fseek(files->outputFirst, pos, SEEK_SET);
    write_output_record(files->outputFirst, record);

    /*INSERT ON BEST*/
	pos = search_insertion(files->outputBest, lists, size);           // TODO: corrigir t_list
	fseek(files->outputBest, pos, SEEK_SET);
    write_output_record(files->outputBest, record);

    /*INSERT ON WORST*/
    pos = search_insertion(files->outputWorst, lists, size);           // TODO: corrigir t_list
    fseek(files->outputWorst, pos, SEEK_SET);
    write_output_record(files->outputWorst, record);
    free_record(record);
}
