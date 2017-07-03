#include <stdlib.h>
#include <stdio.h>

#include <string.h> // strcmp
#include <stdbool.h>
#include <utils.h>
#include <search.h>

int binary_search(int *vector, int begin, int end, int val) {
	if (end < begin) return INVALID;
	int aux = (begin + end)/2;

	if (vector[aux] == val) return aux;
	if (vector[aux] > val) return binary_search(vector, begin, aux - 1, val);
	return binary_search(vector, aux + 1, end, val);
}


void print_menu_remove() {
	printf("Please, give the ticket number to be removed\n");
	printf(">> ");
}


void mark_reg_invalid(FILE *fp, int byteOffset, int nextElement) {
	int regSize, invalid = INVALID;

	// Gets the size of the register
	regSize = get_register_size(fp, byteOffset);

	// Go back to byteOffset
	fseek(fp, byteOffset, SEEK_SET);

	// Mark the record as invalid
	fwrite(&invalid, sizeof(int), 1, fp);

	// Mark the record's size
	fwrite(&regSize, sizeof(int), 1, fp);
	
	// Mark the next in the list
	fwrite(&nextElement, sizeof(int), 1, fp);
	
}


int logical_remove_best_fit_search(FILE *fp, int byteOffset, t_list *list) {
	int pos, next, nextSize;
	int regSize;
	
	regSize = get_register_size(fp, byteOffset);
	
	// Go to the given position
	fseek(fp, byteOffset, SEEK_SET);
	
	// pos starts at the beginning of the list
	pos = list->head;
	
	while (pos != INVALID ) {
		next = next_element(fp, pos, &nextSize);
		
		// if the next element has a smaller (or equal) regsize, go to it
		if (next != INVALID && nextSize <= regSize)
			pos = next;
		
		// we found as far we can go
		else
			break;
	}
	
	// if we didnt find a position in the list, at it to the end of the data file.
	return INVALID;
}



int logical_remove_worst_fit_search(FILE *fp, int byteOffset, t_list *list) {
	int pos, next, nextSize;
	int regSize;
	
	regSize = get_register_size(fp, byteOffset);
	
	// Go to the given position
	fseek(fp, byteOffset, SEEK_SET);
	
	// pos starts at the beginning of the list
	pos = list->head;
	
	while (pos != INVALID ) {
		next = next_element(fp, pos, &nextSize);
		
		// if the next element has a bigger (or equal) regsize, go to it
		if (next != INVALID && nextSize >= regSize)
			pos = next;
		
		// we found as far we can go
		else
			break;
	}
	
	// if we didnt find a position in the list, at it to the end of the data file.
	return INVALID;
}



void logical_remove_best_and_worst(FILE *fp, int byteOffset, t_list *list, char *type) {
	int listOffset, next;
	
	// If the current linked list is empty
	if (list->head == INVALID) { 
		// Add it as a root
		mark_reg_invalid(fp, byteOffset, list->head);
		list->head = byteOffset;
		return;
	}

	// Find the position in the linked list that we need to add the new element
	if ( strcmp(type, "best") == 0)
		listOffset = logical_remove_best_fit_search(fp, byteOffset, list);
	else
		listOffset = logical_remove_worst_fit_search(fp, byteOffset, list);
		
	// If its not the new list root
	if (listOffset != -1) {
		// Goes to the position we will be adding a new element after
		fseek(fp, listOffset, SEEK_SET);
	
		fseek(fp, 2*sizeof(int), SEEK_CUR); // skips the invalid and sizeIndicator
		fread(&next, sizeof(int), 1, fp);	// gets the position of the next element
		
		// pos->next = new element
		fseek(fp, -sizeof(int), SEEK_CUR); 	// we go back to the rewrite the "->next" element
		fwrite(&byteOffset, sizeof(int), 1, fp);
		
		// new element -> next = next
		mark_reg_invalid(fp, byteOffset, next);			
	}
	
	// It is the list root
	else {
		mark_reg_invalid(fp, byteOffset, list->head);
		list->head = byteOffset;
	}
}



void logical_remove_first(FILE *fp, int byteOffset, t_list *list) {
	// Adds the removed register to the beginning of the linked list
	mark_reg_invalid(fp, byteOffset, list->head);	
}


FILE *remove_index(FILE *fp, int ticket, char *file_name) {
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
	for (i = index; i < count -1; i++) {
		tickets[i] = tickets[i+1];
		byteOffsets[i] = byteOffsets[i+1];
	}

	// Clear the file
	fclose(fp);
	fp = fopen(file_name, "w+"); // TODO pode dar bug porque o ponteiro pode ser outro que nao estava no fp antes, precisa testar

	// Write the content back to the index file
	fwrite(tickets, sizeof(int), count-1, fp);
	fwrite(byteOffsets, sizeof(int), count-1, fp);

	// Free the vector
	free(tickets);
	free(byteOffsets);
	
	return fp;
}


void remove_record(t_files *files, t_list *lists) {
	int ticket, byteOffset;
	char *temp;
	bool found;

	while (1) {
		print_menu_remove();
		
		// reads the user input
	    temp = read_line(stdin, FIELD_DELIM, LINE_END, VARIABLE_FIELD);
	    ticket = atoi(temp);
	    free(temp);
	    
		if (ticket >= 0) break;
		printf("Ticket must be a integer greater or equal then zero!!\n\n\n");
	}

	// Best fit
	found = search_primary_index(files->indexBest, ticket, &byteOffset);
	if ( found ) {
		files->indexBest = remove_index(files->indexBest, ticket, "best.idx");
		logical_remove_best_and_worst(files->outputBest, byteOffset, &(lists[BEST]), "best");
		lists[BEST].removed++;
	}
	else
		printf("Ticket was not found in best.idx\n");


	// Worst fit
	found = search_primary_index(files->indexWorst, ticket, &byteOffset);
	if (found) {
		files->indexWorst = remove_index(files->indexWorst, ticket, "worst.idx");
		logical_remove_best_and_worst(files->outputWorst, byteOffset, &(lists[WORST]), "worst");
		lists[WORST].removed++;
	}
	else
		printf("Ticket was not found in worst.idx\n");

	// First fit
	found = search_primary_index(files->indexFirst, ticket, &byteOffset);
	if (found) {
		files->indexFirst = remove_index(files->indexFirst, ticket, "first.idx");	
		logical_remove_first(files->outputFirst, byteOffset, &(lists[FIRST]));
		fclose(files->outputFirst);
		files->outputFirst = fopen("first.dat", "r+");
		lists[FIRST].removed++;
	}
	else
		printf("Ticket was not found in first.idx\n");
		
}
