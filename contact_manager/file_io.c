#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "file_io.h"
#include "contacts.h"

// Maximum path length
#define MAX_PATH 300

static char csv_path[MAX_PATH];

// Ensure storage directory exists and set CSV path
void ensure_storage_path(void) {
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Cannot determine HOME directory.\n");
        exit(1);
    }
    // Build the folder path: $HOME/.local/share/contact_manager
    char dir_path[MAX_PATH];
    snprintf(dir_path, MAX_PATH, "%s/.local/share/contact_manager", home);

    // Create directory if it doesn't exist
    int ret = mkdir(dir_path, 0700);
    if (ret != 0 && errno != EEXIST) {
    perror("Failed to create storage directory");
    exit(1);
    }

    // Set CSV file path
    snprintf(csv_path, MAX_PATH, "%s/contacts.csv", dir_path);
}

// Load contacts from CSV
void load_contacts(void) {
    ensure_storage_path();

    FILE *fp = fopen(csv_path, "r");
    if (!fp) {
        // File doesn't exist, create it with header
        fp = fopen(csv_path, "w");
        if (!fp) {
            perror("Error creating CSV file");
            return;
        }
        fprintf(fp, "id,first_name,last_name,phone_number,email\n");
        fclose(fp);
        return;
    }
    
    char line[300];
    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp) && count < MAX_CONTACTS) {
        int id;
        char fn[MAX_FN] = "", ln[MAX_LN] = "", ph[MAX_PH] = "", em[MAX_EM] = "";

                                                                                           if (sscanf(line, "%d,%49[^,],%49[^,],%19[^,],%99[^\n]",                                       &id, fn, ln, ph, em) == 5) {
            ids[count] = id;
            strcpy(first_names[count], fn);                                                    strcpy(last_names[count], ln);
            strcpy(phone_numbers[count], ph);
            strcpy(emails[count], em);
            count++;
        }
    }
    
    fclose(fp);
 }

// Save contacts to CSV
void save_contacts(void) {
    FILE *fp = fopen(csv_path, "w");
    if (!fp) {
        perror("Error opening CSV file for writing");
	return;
    }
    fprintf(fp, "id,first_name,last_name,phone_number,email\n");
    for (int i = 0; i < count; i++) {
	    fprintf(fp, "%d,%s,%s,%s,%s\n",
	    ids[i], first_names[i], last_names[i], phone_numbers[i], emails[i]);
    }
    fclose(fp);
    printf("Contacts saved successfully.\n");
}
