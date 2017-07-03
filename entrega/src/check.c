#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <ctype.h> 	// isdigit
#include <string.h>	// strlen

#include <utils.h>



bool checkSize(char *string) {
    return strlen(string) == FIXED_SIZE-1 ? true : false;
}


bool checkInputDocument(char *doc) {
	// example of a valid input : 000.394.411/0001-09
	if(!checkSize(doc)) {
        printf("\n\n");
        printf("#Size is not what is expected#\n");
        free(doc);
        printf("\n\n");
        return false;
    }



	// Verifies the size of the input and the special characters.
	if ( strlen(doc) >= FIXED_SIZE || doc[3] != '.' || doc[7] != '.' ||
		 doc[11] != '/' || doc[16] != '-') {
            printf("\n\n");
            printf("#Not a valid field format#\n");
            free(doc);
            printf("\n\n");
		 	return false;
    }
	
	// Verifies the digits
	if ( isdigit(doc[0]) && isdigit(doc[1]) && isdigit(doc[2]) && isdigit(doc[4]) && 
		 isdigit(doc[5]) && isdigit(doc[6]) && isdigit(doc[8]) && isdigit(doc[9]) && 
		 isdigit(doc[10]) && isdigit(doc[12]) && isdigit(doc[13]) && isdigit(doc[14]) && 
		 isdigit(doc[15]) && isdigit(doc[17]) && isdigit(doc[18]) ) return true;

    printf("\n\n");
    printf("#Not a valid field format#\n");
    free(doc);
    printf("\n\n");
	return false;
}


bool checkInputDateAndTime(char *date) {
	/* Example of a valid input: 17/12/2004 17:03:07
		if its a single digit date/time, we consider there is a leading zero.
		Ex: 04/02/2004 08:03:07 */

    if(!checkSize(date)) {
        printf("\n\n");
        printf("#Size is not what is expected#\n");
        free(date);
        printf("\n\n");
        return false;
    }
	
	// Verifies the size of the input and the special characters
	if (strlen(date) >= FIXED_SIZE || date[2] != '/' || date[5] != '/' || 
		date[10] != ' ' || date[13] != ':' || date[16] != ':') {
            printf("\n\n");
            printf("#Not a valid field format#\n");
            free(date);
            printf("\n\n");
            return false;
    }
		
	// Verifies the digits
	if( isdigit(date[0]) && isdigit(date[1]) && isdigit(date[3]) && isdigit(date[4]) && 
		isdigit(date[6]) && isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9]) && 
		isdigit(date[11]) && isdigit(date[12]) && isdigit(date[14]) && isdigit(date[15]) && 
		isdigit(date[17]) && isdigit(date[18]) ) return true;

    printf("\n\n");
    printf("#Not a valid field format#\n");
    free(date);
    printf("\n\n");
	return false;
}


