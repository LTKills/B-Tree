#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <quick.h>
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
    int **first = calloc(2, sizeof(int*)),
        **best = calloc(2, sizeof(int*)),
        **worst = calloc(2, sizeof(int*));
   int pos = -1, size, nfirst, nbest, nworst, i;


    record = print_insert_menu();
    size = calculate_size(record);

    /*Defragment files*/
    if(get_register_size(files->outputFirst, pos) != 0) {
        lists[FIRST].fragmentation++;
        if(lists[FIRST].fragmentation > 5)
            lists[FIRST] = defragment(lists[FIRST], files, FIRST);
    }


    /*INSERT ON OUTPUT FILES*/
    /*FIRST*/
    pos = search_insertion(files->outputFirst, lists, size);
    fseek(files->outputFirst, pos, SEEK_SET);
    write_output_record(files->outputFirst, record);

    /*Defragment files*/
    if(get_register_size(files->outputFirst, pos) != 0){
        lists[FIRST].fragmentation++;
        if(lists[FIRST].fragmentation > 5)
            lists[FIRST] = defragment(lists[FIRST], files, FIRST);
    }


    /*BEST*/
    pos = search_insertion(files->outputBest, lists, size);
    fseek(files->outputBest, pos, SEEK_SET);
    write_output_record(files->outputBest, record);

    /*Defragment files*/
    if(get_register_size(files->outputBest, pos) != 0) {
        lists[BEST].fragmentation++;
        if(lists[BEST].fragmentation > 5)
            lists[BEST] = defragment(lists[BEST], files, BEST);
    }


    /*WORST*/
    pos = search_insertion(files->outputWorst, lists, size);
    fseek(files->outputWorst, pos, SEEK_SET);
    write_output_record(files->outputWorst, record);

    /*Defragment files*/
    if(get_register_size(files->outputWorst, pos) != 0) {
        lists[WORST].fragmentation++;
        if(lists[WORST].fragmentation > 5)
            lists[WORST] = defragment(lists[WORST], files, WORST);
    }


    /*INSERT ON INDEX FILES*/
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

    first[0] = malloc(sizeof(int)*((nfirst/2) + 1));
    first[1] = malloc(sizeof(int)*((nfirst/2) + 1));

    worst[0] = malloc(sizeof(int)*((nworst/2) + 1));
    worst[1] = malloc(sizeof(int)*((nworst/2) + 1));

    best[0] = malloc(sizeof(int)*((nbest/2) + 1));
    best[1] = malloc(sizeof(int)*((nbest/2) + 1));

    fread(first[0], sizeof(int), nfirst/2, files->indexFirst);
    fread(first[1], sizeof(int), nfirst/2, files->indexFirst);
    first[0][nfirst/2] = record->ticket;
    first[1][nfirst/2] = pos;

    fread(worst[0], sizeof(int), nworst/2, files->indexWorst);
    fread(worst[1], sizeof(int), nworst/2, files->indexWorst);
    worst[0][nworst/2] = record->ticket;
    worst[1][nworst/2] = pos;

    fread(best[0], sizeof(int), nbest/2, files->indexBest);
    fread(best[1], sizeof(int), nbest/2, files->indexBest);
    best[0][nbest/2] = record->ticket;
    best[1][nbest/2] = pos;

    quickSort(first, 0, nfirst/2);
    quickSort(worst, 0, nworst/2);
    quickSort(best, 0, nbest/2);


    /*Go back to the beginning again and write data*/
    fseek(files->indexFirst, 0, SEEK_SET);
    fseek(files->indexWorst, 0, SEEK_SET);
    fseek(files->indexBest, 0, SEEK_SET);

    fwrite(first[0], sizeof(int), nfirst/2 + 1, files->indexFirst);
    fwrite(first[1], sizeof(int), nfirst/2 + 1, files->indexFirst);

    fwrite(best[0], sizeof(int), nbest/2 + 1, files->indexBest);
    fwrite(best[1], sizeof(int), nbest/2 + 1, files->indexBest);

    fwrite(worst[0], sizeof(int), nworst/2 + 1, files->indexWorst);
    fwrite(worst[1], sizeof(int), nworst/2 + 1, files->indexWorst);


    /*Deallocate*/
    for(i = 0; i < 2; i++) {
        free(first[i]);
        free(best[i]);
        free(worst[i]);
    }

    
    free(first);
    free(best);
    free(worst);
    free_record(record);
}
