#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <utils.h>


/*Searches a given primary index for a given ticket using binary search. 
	Returns true if found, false otherwise. 
	Using *byteOffset, we return the offset the field was found. */
bool search_primary_index(FILE *index, int ticket, int *byteOffset) {
	int count, start, end, middle, fileSize, limitTicketBO;
	int *tickets, *byteOffsets;
	bool found = false;
	
	// Getting the size of the file
	fseek(index, 0, SEEK_END);
	fileSize = ftell(index);
	fseek(index, 0, SEEK_SET);
	
	// Position of first byte offset
	limitTicketBO = fileSize / 2;
	count = limitTicketBO/sizeof(int);
		
	// Initializing needed memory
	tickets = malloc(sizeof(int)*count);
	byteOffsets = malloc(sizeof(int)*count);
	
	fseek(index, 0, SEEK_SET);
	
	// Reading to memory the key and byte offsett
	fread(tickets, sizeof(int), count, index);
	fread(byteOffsets, sizeof(int), count, index);
	
	end = count - 1;
	start = 0;

	while(end >= start) {
		middle = (start+end)/2;
		
		if(ticket > tickets[middle]) start = middle+1; // if query comes later
		
		else if(ticket < tickets[middle]) end = middle-1; 	// if query comes sooner
		
		else if(ticket == tickets[middle]) { // if we found the wanted query
			found = true;
			*byteOffset = byteOffsets[middle];
			
			free(tickets);
			free(byteOffsets);
			return found;
		}      
	}
    
    // the query was not found therefore it does not exist in the primary index
    *byteOffset = INVALID;

    free(tickets);
    free(byteOffsets);
    return false;
}



int search_insertion(FILE *output, t_list *list, int neededSize) {
	int pos, posSize, nextSize, next;
	
	// If there is no space to be reused, insert at the end of the data file
	if (list->head == INVALID)
		return get_file_size(output);
	
	pos = list->head;
	fseek(output, pos + sizeof(int), SEEK_SET); 
    fread(&posSize, sizeof(int), 1, output);
	fread(&next, sizeof(int), 1, output);  
    
    // Removing at the head
    if (posSize >= neededSize) {
    	list->head = next;
    	return pos;
    }
	
	
	// Searches the list for a valid position
	while (pos != INVALID ) {
		fseek(output, pos + sizeof(int), SEEK_SET); 
	    fread(&posSize, sizeof(int), 1, output);  
	
		next = next_element(output, pos, &nextSize);
		
		// if the next element has a smaller (or equal) regsize, go to it
		if (next != INVALID && nextSize >= neededSize) {
			break;
		} 
		else if (next != INVALID)
			pos = next;
		else
			break;
	}
	
	// If there is a valid position, change the previous node's next pointer
	if (next != INVALID && nextSize >= neededSize) {
		int newNextSize, newNext;
		newNext = next_element(output, next, &newNextSize); // after = next->next;		
		
		fseek(output, pos + 2*sizeof(int), SEEK_SET); 
		fwrite(&newNext, sizeof(int), 1, output); // pos->next = after;
		
		return next;
	}
	
	// No available reusable space was found, so we insert at the end of the data file
	return get_file_size(output);
}



