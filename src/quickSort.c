/*
 * =====================================================================================
 *
 *       Filename:  quick.c
 *
 *    Description:  Quick sort implementation
 *
 *        Version:  1.0
 *        Created:  11/29/16 23:06:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LTKills
 *   Organization:  The University of Sao Paulo
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <utils.h>


/*Divides into bigger than pivot to right and lower to left*/
int partition(int **vec, int start, int end) {
	int i = start-1, j = end+1, pivot = vec[0][start];

	while(i < j) {

		do { // Go from the begining
			i++;
		} while(vec[0][i] < pivot);

		do { // Go from the end
			j--;
		} while(vec[0][j] > pivot);

		if(i >= j) break;

		swap(vec, i, j);
	}

	return j; // Where to divide next
}

/*Recursion to call partition*/
void quickSort(int **vec, int start, int end) {
	int pivot;

	if(end > start) {
		pivot = partition(vec, start, end); // Partitions vector before recusive call
		quickSort(vec, start, pivot);
		quickSort(vec, pivot+1, end);
	}
}


