#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <search.h>
#include <check.h>

void print_menu_remove() {
	printf("Please, give the ticket number to be removed\n");
	printf(">> ");
}

void remove_record(t_files *files, t_list *list) {
	int ticket;

	while (1) {
		print_menu_remove();
		scanf("%d", &ticket);
		if (ticket > 0) break;
		printf("Ticket must be a integer greater then zero\n");
	}

}