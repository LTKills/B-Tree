#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

/*Searches a given index for a given index using binary search. 
	Returns true if found, false otherwise. 
	Using *byteOffset, we return the offset the field was found. */
bool search_primary_index(FILE *index, int ticket, int *byteOffset) {
	int count, start, end, middle, fileSize, limitTicketBO;
	int *tickets, *byteOffsets;
	bool found = false;
	
	fseek(index, 0, SEEK_END);
	fileSize = ftell(index);
	fseek(index, 0, SEEK_SET);
	
	// Position of first byte offset
	limitTicketBO = fileSize / 2;
	count = limitTicketBO/sizeof(int);
		
	tickets = malloc(sizeof(int)*count);
	byteOffsets = malloc(sizeof(int)*count);
	
	fread(tickets, count, sizeof(int), index);
	fread(byteOffsets, count, sizeof(int), index);
	
	end = count - 1;
	start = 0;
	
	 while(end >= start) {
        middle = (start+end)/2;
        if(ticket > tickets[middle]) start = middle+1; // if query comes later
        else if(ticket < tickets[middle]) end = middle-1; 	// if query comes sooner
        else if(ticket == tickets[middle]) {
        	found = true;
			*byteOffset = (limitTicketBO) + middle*sizeof(int);
			return found;
        }      
    }
    
    *byteOffset = -1;
    return false;
}



bool search_insertion_first_fit(FILE *index, int ticket, int *byte_offset) {
		
	return true;


}
