#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <search.h>

void print_menu_remove() {
	printf("Please, give the ticket number to be removed\n");
	printf(">> ");
}

void logial_remove(FILE *fp, int pos, t_list *list) {
	int counter = 0, invalid = -1;
	char aux = 'a';

	// Go to 'pos'
	fseek(fp, pos, SEEK_SET);

	// Go to the end of the record to count it's size
	while (!feof(fp) && aux != '#') {
		fread(&aux, sizeof(char), 1, fp);
		if (!feof(fp)) counter++;
	}

	// Go back to pos
	fseek(fp, pos, SEEK_SET);

	// Mark the record as invalid
	fwrite(&invalid, sizeof(int), 1, fp);	
	
	// Mark the record's size
	fwrite(&counter, sizeof(int), 1, fp);

	// Mark the next in the list
	// fwrite top da lista

}

void remove_record(t_files *files, t_list *list) {
	int ticket, byteOffset;

	while (1) {
		print_menu_remove();
		scanf("%d", &ticket);
		if (ticket > 0) break;
		printf("Ticket must be a integer greater then zero\n");
	}

	// Best fit
	// byteOffset = busca_no_arquivo_de_indice_best
	logial_remove(files->outputBest, byteOffset, list);
	// list->best = byteOffset;

	// Worst fit
	// byteOffset = busca_no_arquivo_de_indice_worst
	logial_remove(files->outputWorst, byteOffset, list);
	// list->worst = byteOffset;

	// First fit 
	// byteOffset = busca_no_arquivo_de_indice_first
	logial_remove(files->outputFirst, byteOffset, list);
	// list->first = byteOffset;
}