#include <stdio.h>
#include <string.h>
#include "contacts.h"

char first_names[500][50];
char last_names[500][50];
char emails[500][100];
char phone_numbers[500][20];
int ids[500];
int count = 0;

int generate_id() {
	if (count == 0) return 1;
	return ids[count - 1] + 1;
}

void add_contact() {
	char fn[50], ln[50], ph[20], em[100];


	printf("First Name: "); fgets(fn, 50, stdin); fn[strcspn(fn, "\n")] = 0;
	printf("Last Name: "); fgets(ln, 50, stdin); ln[strcspn(ln, "\n")] = 0;
	printf("Phone Number: "); fgets(ph, 20, stdin); ph[strcspn(ph, "\n")] = 0;
	printf("Email: "); fgets(em, 100, stdin); em[strcspn(em, "\n")] = 0;


	ids[count] = generate_id();
	strcpy(first_names[count], fn);
	strcpy(last_names[count], ln);
	strcpy(phone_numbers[count], ph);
	strcpy(emails[count], em);


	count++;


	printf("Contact added successfully!\n");
}


void list_contacts() {
	printf("\nID | First Name | Last Name | Phone | Email\n");
	printf("-------------------------------------------------------------\n");


	for (int i = 0; i < count; i++) {
		printf("%d | %s | %s | %s | %s\n", ids[i], first_names[i], last_names[i], phone_numbers[i], emails[i]);
	}
}

void show_contact_by_id() {
	int id;
	printf("Enter ID: "); scanf("%d", &id); getchar();


	for (int i = 0; i < count; i++) {
		if (ids[i] == id) {
			printf("\nID: %d\nFirst: %s\nLast: %s\nPhone: %s\nEmail: %s\n",
					ids[i], first_names[i], last_names[i], phone_numbers[i], emails[i]);
			return;
		}
	}

	printf("Contact not found.\n");
}


void delete_contact_by_id() {
	int id;
	printf("Enter ID: "); scanf("%d", &id); getchar();


	int index = -1;
	for (int i = 0; i < count; i++) {
		if (ids[i] == id) { index = i; break; }
	}
	if (index == -1) {
		printf("Contact not found.\n");
		return;
	}


	for (int i = index; i < count - 1; i++) {
		ids[i] = ids[i+1];
		strcpy(first_names[i], first_names[i+1]);
		strcpy(last_names[i], last_names[i+1]);
		strcpy(phone_numbers[i], phone_numbers[i+1]);
		strcpy(emails[i], emails[i+1]);
	}


	count--;


	printf("Contact deleted.\n");
}


void update_contact_by_id() {
	int id;
	printf("Enter ID: "); scanf("%d", &id); getchar();


	for (int i = 0; i < count; i++) {
		if (ids[i] == id) {
			char fn[50], ln[50], ph[20], em[100];


			printf("New First Name (%s): ", first_names[i]); fgets(fn, 50, stdin); fn[strcspn(fn, "\n")] = 0;
			printf("New Last Name (%s): ", last_names[i]); fgets(ln, 50, stdin); ln[strcspn(ln, "\n")] = 0;
			printf("New Phone (%s): ", phone_numbers[i]); fgets(ph, 20, stdin); ph[strcspn(ph, "\n")] = 0;
			printf("New Email (%s): ", emails[i]); fgets(em, 100, stdin); em[strcspn(em, "\n")] = 0;


			if (strlen(fn) > 0) strcpy(first_names[i], fn);
			if (strlen(ln) > 0) strcpy(last_names[i], ln);
			if (strlen(ph) > 0) strcpy(phone_numbers[i], ph);
			if (strlen(em) > 0) strcpy(emails[i], em);


			printf("Contact updated.\n");
			return;
		}
	}


	printf("Contact not found.\n");
}
