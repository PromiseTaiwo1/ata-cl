#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "file_io.h"
#include "contacts.h"

/* Maximum path length (safe default on Linux) */
#define MAX_PATH 512

static char csv_path[MAX_PATH];

/* Ensure storage directory exists and set CSV path */
void ensure_storage_path(void) {
                const char *home = getenv("HOME");
	        if (!home) {
			        fprintf(stderr, "Error: Cannot determine HOME directory.\n");
				        exit(EXIT_FAILURE);
					    }

		    /* Build directory path: $HOME/.local/share/contact_manager */
		    char dir_path[MAX_PATH];
		        int n = snprintf(dir_path, MAX_PATH,
					                     "%s/.local/share/contact_manager", home);

			    if (n < 0 || n >= MAX_PATH) {
				            fprintf(stderr, "Error: Storage path too long.\n");
					            exit(EXIT_FAILURE);
						        }

			        /* Create directory if it does not exist */
			        if (mkdir(dir_path, 0700) != 0 && errno != EEXIST) {
					        perror("Error creating storage directory");
						        exit(EXIT_FAILURE);
							    }

				    /* Build CSV file path */
				    n = snprintf(csv_path, MAX_PATH, "%s/contacts.csv", dir_path);
				        if (n < 0 || n >= MAX_PATH) {
						        fprintf(stderr, "Error: CSV path too long.\n");
							        exit(EXIT_FAILURE);
								    }
}

/* Load contacts from CSV */
void load_contacts(void) {
	    ensure_storage_path();

	        FILE *fp = fopen(csv_path, "r");
		    if (!fp) {
			            /* File does not exist: create it with header */
			            fp = fopen(csv_path, "w");
				            if (!fp) {
						                perror("Error creating CSV file");
								            return;
									            }

					            fprintf(fp, "id,first_name,last_name,phone_number,email\n");
						            fclose(fp);
							            return;
								        }

		        char line[512];
			    fgets(line, sizeof(line), fp); /* skip header */

			        while (fgets(line, sizeof(line), fp) && count < MAX_CONTACTS) {
					        int id;
						        char fn[MAX_FN] = "";
							        char ln[MAX_LN] = "";
								        char ph[MAX_PH] = "";
									        char em[MAX_EM] = "";

										        if (sscanf(line,
														                   "%d,%49[^,],%49[^,],%19[^,],%99[^\n]",
																                      &id, fn, ln, ph, em) == 5) {

												            ids[count] = id;
													                strcpy(first_names[count], fn);
															            strcpy(last_names[count], ln);
																                strcpy(phone_numbers[count], ph);
																		            strcpy(emails[count], em);
																			                count++;
																					        }
											    }

				    fclose(fp);
}

/* Save contacts to CSV */
void save_contacts(void) {
	    FILE *fp = fopen(csv_path, "w");
	        if (!fp) {
			        perror("Error opening CSV file for writing");
				        return;
					    }

		    fprintf(fp, "id,first_name,last_name,phone_number,email\n");

		        for (int i = 0; i < count; i++) {
				        fprintf(fp, "%d,%s,%s,%s,%s\n",
							                ids[i],
									                first_names[i],
											                last_names[i],
													                phone_numbers[i],
															                emails[i]);
					    }

			    fclose(fp);
			        printf("Contacts saved successfully.\n");
}

