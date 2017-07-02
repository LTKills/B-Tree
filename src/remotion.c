#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <search.h>

int binary_search(int *vector, int begin, int end, int val) {
	if (end < begin) return -1;
	int aux = (begin + end)/2;

	if (vector[aux] == val) return aux;
	if (vector[aux] > val) return binary_search(vector, begin, aux - 1, val);
	return binary_search(vector, aux + 1, end, val);
}

void print_menu_remove() {
	printf("Please, give the ticket number to be removed\n");
	printf(">> ");
}

void logical_remove(FILE *fp, int pos, int top) {
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
	fwrite(&top, sizeof(int), 1, fp);
}

void remove_index(FILE *fp, int ticket, char *file_name) {
	int i, fileSize, limitTicketBO, count, index;
	int *tickets, *byteOffsets;

	// Getting the size of the file
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	// Position of first byte offset
	limitTicketBO = fileSize / 2;
	count = limitTicketBO/sizeof(int);
		
	// Initializing needed memory
	tickets = malloc(sizeof(int)*count);
	byteOffsets = malloc(sizeof(int)*count);
	
	// Reading to memory the key and byte offsett
	fread(tickets, sizeof(int), count, fp);
	fread(byteOffsets, sizeof(int), count, fp);

	// Search for the index of the ticket
	index = binary_search(tickets, 0, count-1, ticket);

	// Shift the vector
	for (i = index + 1; i < count; i++) {
		tickets[i] = tickets[i-1];
		byteOffsets[i] = byteOffsets[i-1];
	}

	// Clear the file
	fclose(fp);
	fp = fopen(file_name, "w"); // pode dar bug porque o ponteiro pode ser outro que nao estava no fp antes, precisa testar

	// Write the content back to the file
	fwrite(tickets, count-1, sizeof(int), fp);
	fwrite(byteOffsets, count-1, sizeof(int), fp);

	// Free the vector
	free(tickets);
	free(byteOffsets);
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
	// logial_remove(files->outputBest, byteOffset, list->best);
	remove_index(files->indexBest, ticket, "best.idx");
	// list->best = byteOffset;

	// Worst fit
	// byteOffset = busca_no_arquivo_de_indice_worst
	// logial_remove(files->outputWorst, byteOffset, list->worst);
	remove_index(files->indexWorst, ticket, "worst.idx");
	// list->worst = byteOffset;

	// First fit
	// byteOffset = busca_no_arquivo_de_indice_first
	// logial_remove(files->outputFirst, byteOffset, list->first);
	remove_index(files->indexFirst, ticket, "first.idx");
	// list->first = byteOffset;
}