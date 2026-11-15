#include <stdio.h>
#include <string.h>
#include "contact.h"

// delete the contact
void delete_contact(AddressBook *addressbook)
{
    // If no contacts exist, exit early
    if (addressbook->contact_count == 0) 
    {
        printf("No contacts to delete.\n");
        return;
    }

    int a;  // control variable for loop (repeat deletion)
    do {
        int searchChoice;
        // Prompt user for search criteria
        printf("\nSearch contact to delete by:\n");
        printf("1. Name\n2. Mobile Number\n3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &searchChoice);

        char search[40]; // buffer for search input
        if (searchChoice == 1)
        {
            printf("Enter the name: ");
            scanf(" %[^\n]", search); // read full name with spaces
        }
        else if (searchChoice == 2) 
        {
            printf("Enter the mobile number: ");
            scanf(" %s", search); // read mobile number
        } 
        else if (searchChoice == 3) 
        {
            printf("Enter the email: ");
            scanf(" %s", search); // read email
        } 
        else 
        {
            printf("Invalid choice.\n");
            continue;   // go back to start of delete loop
        }

        int matches[100], count = 0; // store indices of matched contacts
        for (int i = 0; i < addressbook->contact_count; i++) 
        {
            Contacts *entry = &addressbook->contact_details[i];
            // Check if search string matches Name, Mobile, or Email
            if ((searchChoice == 1 && strstr(entry->Name, search) != NULL) ||
                (searchChoice == 2 && strstr(entry->Mobile_number, search) != NULL) ||
                (searchChoice == 3 && strstr(entry->Mail_ID, search) != NULL)) 
            {
                matches[count++] = i; // store index of match
            }
        }

        if (count == 0) 
        {
            // No matches found
            printf("Contact not found.\n");
        } 
        else 
        {
            // Handle duplicate names
            if (count > 1 && searchChoice == 1) 
            {
                printf("\nMultiple contacts found with the same name.\n");
                for (int k = 0; k < count; k++) 
                {
                    int idx = matches[k];
                    // Print all duplicates
                    printf("%d. Name   : %s\n", k+1, addressbook->contact_details[idx].Name);
                    printf("   Mobile : %s\n", addressbook->contact_details[idx].Mobile_number);
                    printf("   Email  : %s\n", addressbook->contact_details[idx].Mail_ID);
                    printf("-------------------------------------------------\n");
                }

                // Ask user to refine search
                printf("Refine search:\n1. By Mobile Number\n2. By Email\nEnter choice: ");
                int refineChoice;
                scanf("%d", &refineChoice);

                printf("Enter value: ");
                scanf(" %s", search);

                count = 0;
                // Search again using refined criteria
                for (int i = 0; i < addressbook->contact_count; i++) 
                {
                    Contacts *entry = &addressbook->contact_details[i];
                    if ((refineChoice == 1 && strstr(entry->Mobile_number, search) != NULL) ||
                        (refineChoice == 2 && strstr(entry->Mail_ID, search) != NULL)) 
                    {
                        matches[count++] = i;
                    }
                }

                if (count == 0) 
                {      // after refined search then also count=0 means no contact found 
                    printf("No contact found with that refinement.\n");
                }
            }

            // Display the first matched contact and confirmation of the  deletion
            if (count > 0) 
            {
                Contacts *entry = &addressbook->contact_details[matches[0]];
                printf("\n--- Contact Found ---\n");
                printf("Name : %s\nMobile : %s\nEmail  : %s\n",
                       entry->Name, entry->Mobile_number, entry->Mail_ID);

                char confirm;
                printf("\nAre you sure you want to delete this contact? (y/n): ");
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y')
                {
                    int idx = matches[0];
                    // Shift all contacts after the deleted one up by one
                    for (int j = idx; j < addressbook->contact_count - 1; j++) 
                    {
                        addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                    }
                    addressbook->contact_count--; // reduce count
                    printf("Contact deleted successfully!\n");
                } 
                else 
                {
                    printf("Deletion cancelled.\n"); //cancel the function
                }
            }
        }

        // Ask if user wants to delete another contact
        printf("\nDo you want to delete another contact?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &a);

    } while (a== 1); // repeat if user chooses Yes
}

