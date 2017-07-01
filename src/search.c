#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

/*Searches a given index for a given index using binary search. 
	Returns true if found, false otherwise. 
	Using *byteOffset, we return the offset the field was found. */
bool search_primary_index(FILE *index, int ticket, int *byte_offset) {
	int pos, fileSize;
	
	fseek(index, 0, SEEK_END);
	fileSize = ftell(index);
	fseek(index, 0, SEEK_SET);


}
