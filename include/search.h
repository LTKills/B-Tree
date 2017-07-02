#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <stdbool.h>


bool search_primary_index(FILE *index, int ticket, int *byteOffset);

int search_insertion(FILE *output, t_list list, int neededSize);

#endif
