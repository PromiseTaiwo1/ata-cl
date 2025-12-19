#ifndef CONTACTS_H
#define CONTACTS_H

#define MAX_CONTACTS 500
#define MAX_FN 50
#define MAX_LN 50
#define MAX_EM 100
#define MAX_PH 20

extern char first_names[500][50];
extern char last_names[500][50];
extern char emails[500][100];
extern char phone_numbers[500][20];
extern int ids[500];
extern int count;


void add_contact(void);
void list_contacts(void);
void show_contact_by_id(void);
void update_contact_by_id(void);
void delete_contact_by_id(void);


#endif#ifndef CONTACTS_H
#define CONTACTS_H

#define MAX_CONTACTS 500
#define MAX_FN 50
#define MAX_LN 50
#define MAX_EM 100
#define MAX_PH 20

extern char first_names[500][50];
extern char last_names[500][50];
extern char emails[500][100];
extern char phone_numbers[500][20];
extern int ids[500];
extern int count;


void add_contact(void);
void list_contacts(void);
void show_contact_by_id(void);
void update_contact_by_id(void);
void delete_contact_by_id(void);


#endif
