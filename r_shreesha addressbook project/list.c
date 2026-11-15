#include <stdio.h>
#include <string.h>
#include "contact.h"
void list_contacts(AddressBook *addressbook)
{
    //if count_count is 0 then print no contact found
     if (addressbook->contact_count == 0) 
    {
        printf("No contacts to display.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    //looping till i bcoz to access all the slots in the contact_details 
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        // Temporary variable for clarity
        Contacts c = addressbook->contact_details[i];
        printf("%d. %s | %s | %s\n", i + 1, c.Name, c.Mobile_number, c.Mail_ID);
    }
}
