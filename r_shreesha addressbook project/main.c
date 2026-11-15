/*
 Address Book Project Documentation

1. Introduction
---------------
This project implements a menu-driven Address Book  software application in C.
It allows users to manage contacts by adding, searching, editing,
deleting, displaying, saving, and loading them from a file. which works simillar to that of the telephone dairies
since we have some diadvantages with that of the telephone dairies(hardcopy) like to edit,delete and search which might take lot of time 
so this can be replaced by the software application.
The program demonstrates the use of structures, arrays, file handling,
and modular programming in C. 


2. Features
-----------
- Add Contact: Create a new contact with name, mobile number, and email.
- Search Contact: Search by name, mobile number, or email. Handles duplicates.
- Edit Contact: Modify an existing contact’s details.
- Delete Contact: Remove a contact from the list.
- Display Contacts: Show all saved contacts.
- Save Contacts: Write contacts to a CSV file (contacts.csv).
- Load Contacts: Read contacts from the CSV file at startup.
- Exit: Quit the program safely.

3. Data Structures
------------------
typedef struct 
{
    char Name[30];
    char Mobile_number[15];
    char Mail_ID[40];
} Contacts;

typedef struct
 {
    Contacts contact_details[100]; // array of contacts
    int contact_count;             // number of contacts stored
} AddressBook;

4. Program Flow
---------------
- Initialization:
  contact_count is set to 0, load_contacts() loads existing contacts,
  list_contacts() displays them.
- Menu Loop:
  Displays options and executes corresponding functions until Exit.
- File Handling:
  Contacts are saved in contacts.csv. First line stores count (#N),
  subsequent lines store contact details.

5. Validations
-------------
- Name Validation: Only alphabets and spaces.
- Mobile Validation: 10-digit numeric input, no duplicates.
- Email Validation:
  * No spaces
  * Only lowercase letters, digits, '@', '.', '_'
  * Exactly one '@'
  * '@' not at start or end
  * Must end with ".com"
  * Must have domain name between '@' and '.com'
  * Must start with a lowercase letter
  * No duplicates

6. Example Usage
----------------
Address book menu
1.Add contact
2.search contact
3.Edit contact
4.Delete contact
5.Display contact
6.Save contact
7.Exit
Enter the option : 1
Enter Name: shreesha
Enter Mobile number: 9876543210
Enter Email: shreesha@gmail.com
Contact created successfully!

7. File Format
--------------
Example contacts.csv:
#2
shreesha,9876543210,shreesha@gmail.com
Sita,9123456789,sita@gmail.com

8. Conclusion
-------------
This project demonstrates:
- Structs and arrays for data management
- Functions for modular design
- File I/O for persistence
- Validation for robust input handling
*/

#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structure definition */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;
    load_contacts(&addressbook);
    list_contacts(&addressbook);

    while (1)
    {
        printf("\nAddress book menu\n"); /* Give a prompt message for a user */
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n");
        printf("Enter the option : ");
        scanf("%d", &option);

        switch (option) /* Based on chosen option */
        {
        case 1: 
        {
            create_contact(&addressbook); 
              break;
        }
        case 2: 
        {
            search_contacts(&addressbook); 
            break;
        }
        case 3: 
        {
            edit_contact(&addressbook); 
            break;
        }
        case 4: 
        {
            delete_contact(&addressbook); 
            break;
        }
        case 5: 
        {
            list_contacts(&addressbook);
             break;
        }
        case 6: 
        {
            save_contacts(&addressbook);
             break;
        }
        case 7:
        {
            printf("Exiting Address Book...\n");
            return 0;
        }
        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}
