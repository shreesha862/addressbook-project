#include <stdio.h>
#include <string.h>
#include "contact.h"

void edit_contact(AddressBook *addressbook)
{
    // Check if there are any contacts to edit
    if (addressbook->contact_count == 0) 
    {
        printf("No contacts to edit.\n");
        return;
    }

    int a;   // control variable for loop (repeat editing)
    do {
        int searchChoice;
        // Prompt user for search criteria
        printf("\nSearch contact to edit by:\n");
        printf("1. Name\n2. Mobile Number\n3. Email\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &searchChoice);

        char s[40]; // buffer for search input
        if (searchChoice == 1) 
        {
            printf("Enter the name: ");
            scanf(" %[^\n]", s); // read full name with spaces
        } 
        else if (searchChoice == 2) 
        {
            printf("Enter the mobile number: ");
            scanf(" %s", s); // read mobile number
        } 
        else if (searchChoice == 3) 
        {
            printf("Enter the email: ");
            scanf(" %s", s); // read email
        } 
        else 
        {
            printf("Exit\n");
            return; // exit function if user chooses 4
        }

        int matches[100], count = 0; // store indices of matched contacts
        // Search through all contacts for a match
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            //temporary variable for clarity
            Contacts *entry = &addressbook->contact_details[i];
            if ((searchChoice == 1 && strstr(entry->Name, s) != NULL) ||
                (searchChoice == 2 && strstr(entry->Mobile_number, s) != NULL) ||
                (searchChoice == 3 && strstr(entry->Mail_ID, s) != NULL)) 
            {
                matches[count++] = i; // store index of match
            }
        }

        // If no matches found
        if (count == 0)
        {
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
                    // Display all matching contacts
                    printf("%d. Name   : %s\n", k+1, addressbook->contact_details[idx].Name);
                    printf("   Mobile : %s\n", addressbook->contact_details[idx].Mobile_number);
                    printf("   Email  : %s\n", addressbook->contact_details[idx].Mail_ID);
                    printf("-------------------------------------------------\n");
                }

                // Ask user to refine search
                printf("Re-search again:\n1. By Mobile Number\n2. By Email\nEnter choice: ");
                int refineChoice;
                scanf("%d", &refineChoice);

                printf("Enter value: ");
                scanf(" %s", s);

                count = 0;
                // Search again using refined criteria
                for (int i = 0; i < addressbook->contact_count; i++) 
                {
                    Contacts *entry = &addressbook->contact_details[i];
                    if ((refineChoice == 1 && strstr(entry->Mobile_number, s) != NULL) ||
                        (refineChoice == 2 && strstr(entry->Mail_ID, s) != NULL))
                    {
                        matches[count++] = i;
                    }
                }

                // If still no match after refinement
                if (count == 0) 
                {
                    printf("No contact found with that refinement.\n");
                }
            }

            // If a valid match is found
            if (count > 0) 
            {
                Contacts *entry = &addressbook->contact_details[matches[0]];
                // Display the found contact
                printf("\n--- Contact Found ---\n");
                printf("Name : %s\nMobile : %s\nEmail  : %s\n",
                       entry->Name, entry->Mobile_number, entry->Mail_ID);

                int choice;
                // Ask which field to edit
                printf("\nWhat do you want to edit?\n1. Name\n2. Mobile\n3. Email\nEnter choice: ");
                scanf("%d", &choice);

                // Edit name
                if (choice == 1) 
                {
                    char newName[30];
                    name_validation(newName); // validate new name
                    strcpy(entry->Name, newName); // update name
                } 
                // Edit mobile number
                else if (choice == 2)
                {
                    char newMobile[15];
                    mobile_validation(addressbook, newMobile); // validate new mobile
                    strcpy(entry->Mobile_number, newMobile); // update mobile
                } 
                // Edit email
                else if (choice == 3)
                {
                    char newEmail[40];
                    email_validation(addressbook, newEmail); // validate new email
                    strcpy(entry->Mail_ID, newEmail); // update email
                } 
                else 
                {
                    printf("Invalid choice.\n");
                }

                printf("Contact updated successfully!\n");
            }
        }

        // Ask if user wants to edit another contact
        printf("\nDo you want to edit another contact?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &a);

    } while (a == 1); // repeat if user chooses Yes
}

