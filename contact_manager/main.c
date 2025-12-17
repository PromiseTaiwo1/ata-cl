#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include "contacts.h"

int main() {
    load_contacts(); // load csv on startup
    

    int choice;
    while (1) {
	printf("\n===CONTACT MANAGER==="
	        "\n1. Add Contact"
		"\n2. List Contacts"
		"\n3. Show Contact by ID"
		"\n4. Update Contact"
		"\n5. Delete Contact"
		"\n6. Exit"
		"\nEnter choice: ");
	scanf("%d", &choice);
	getchar();

	switch (choice) {
            case 1: add_contact:(); break;
            case 2: list_contacts(); break;
            case 3: show_contact_by_id(); break;
	    case 4: update_contact_by_id(); break;
	    case 5: delete_contact_by_id(); break;
	    case 6: save_contacts(); exit(0);
	    default: printf("Invalid choice. Try again.\n");
