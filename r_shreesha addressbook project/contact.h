#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>

// Structures for the Fields
typedef struct Contact_data
{
    char Name[20];
    char Mobile_number[11];
    char Mail_ID[30];

} Contacts;

// Structures foe the Contact deatils
typedef struct AddressBook_Data
{
    // Array of structures for the Fields sturucture
    Contacts contact_details[100];
    // To keep the track no of contact count
    int contact_count;
} AddressBook;

//Function declarations or prototype 

void create_contact(AddressBook *);
void list_contacts(AddressBook *);
void search_contacts(AddressBook *);
void edit_contact(AddressBook *);
void delete_contact(AddressBook *);
void save_contacts(AddressBook *);
void load_contacts(AddressBook *);

//  Function declaration of the validations
void name_validation(char *);
void mobile_validation(AddressBook *addressbook, char *);
void email_validation(AddressBook *addressbook, char *);


#endif
// CONTACT_H
// CONTACT_H