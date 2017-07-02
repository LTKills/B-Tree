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
	
	// Reading to memory the key and byte offsett
	fread(tickets, count, sizeof(int), index);
	fread(byteOffsets, count, sizeof(int), index);
	
	end = count - 1;
	start = 0;
	
	
	while(end >= start) {
		middle = (start+end)/2;
		if(ticket > tickets[middle]) start = middle+1; // if query comes later
		
		else if(ticket < tickets[middle]) end = middle-1; 	// if query comes sooner
		
		else if(ticket == tickets[middle]) { // if we found the wanted query
			found = true;
			*byteOffset = (limitTicketBO) + middle*sizeof(int);
			return found;
		}      
	}
    
    // the query was not found therefore it does not exist in the primary index
    *byteOffset = INVALID;
    return false;
}


int search_insertion(FILE *output, t_list list, int neededSize) {
	int pos, availableSize, next;
	
	// If there is no space to be reused, insert at the end of the data file
	if (list.head	== INVALID)
		return get_file_size(output);
	
	pos = list.head;
	
	while (pos != INVALID) {
		fseek(output, pos + 1, SEEK_END); // "+1" so we can skip over "*"
		fread(&availableSize, sizeof(int), 1, output);
		fread(&next, sizeof(int), 1, output);
		
		if (availableSize >= neededSize) {
			rewind(output);
			return pos;
		}
			
		pos = next;
	}
	
	// No available reusable space was found, so we insert at the end of the data file
	return get_file_size(output);
}



