#include <stdio.h>
#include <string.h>
#include "contact.h"

void search_contacts(AddressBook *addressbook)
{
    // If no contacts exist, exit early
    if (addressbook->contact_count == 0) 
    {
        printf("No contacts to search.\n");
        return;
    }

    int a; // variable to check if user wants to search again
    do {
        int searchChoice;
        // Prompt user for search criteria
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Email\n");
        printf("4. Exit\n");
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
            scanf(" %[^\n]", s); // read mobile number
        } 
        else if (searchChoice == 3) 
        {
            printf("Enter the email: ");
            scanf(" %[^\n]", s); // read email
        } 
        else 
        {
            printf("Exit.\n");
            continue;   // skip to next loop iteration
        }

        int matches[100], count = 0; // store indices of matched contacts
        for (int i = 0; i < addressbook->contact_count; i++) 
        {
            Contacts *entry = &addressbook->contact_details[i];

            // Check if s string matches Name, Mobile, or Email
            if ((searchChoice == 1 && strstr(entry->Name, s) != NULL) ||
                (searchChoice == 2 && strstr(entry->Mobile_number, s) != NULL) ||
                (searchChoice == 3 && strstr(entry->Mail_ID, s) != NULL))
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
                //prompting to the user that many contacts have same name
                printf("\nMultiple contacts found with the same name.\n");
                for (int k = 0; k < count; k++) 
                {
                    //dispalying all the contacts so it will be helpfull for the user to re-search again
                    int idx = matches[k];

                    // Prints all duplicates
                    printf("%d. Name   : %s\n", k+1, addressbook->contact_details[idx].Name);
                    printf("   Mobile : %s\n", addressbook->contact_details[idx].Mobile_number);
                    printf("   Email  : %s\n", addressbook->contact_details[idx].Mail_ID);
                    printf("-------------------------------------------------\n");
                }

                // Ask user to research  search
                printf("Re-search again:\n");
                printf("1. By Mobile Number\n");
                printf("2. By Email\n");
                printf("Enter your choice: ");
                int refineChoice;
                scanf("%d", &refineChoice);

                printf("Enter value: ");
                scanf(" %s", s);

                count = 0;
                // Search again using refined criteria
                for (int i = 0; i < addressbook->contact_count; i++)
                 {
                    Contacts *entry = &addressbook->contact_details[i];
                    if ((refineChoice == 1 && strstr(entry->Mobile_number, s) != NULL) ||(refineChoice == 2 && strstr(entry->Mail_ID, s) != NULL)) 
                    {
                        matches[count++] = i;
                    }
                }

                if (count == 0) 
                {
                    printf("No contact found with that refinement.\n");
                }
            }

            // Display the first matched contact
            if (count > 0) 
            {
                int i = matches[0];
                printf("\n--- Contact Found ---\n");
                printf("Name   : %s\n", addressbook->contact_details[i].Name);
                printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
                printf("Email  : %s\n", addressbook->contact_details[i].Mail_ID);
            }
        }

        // Ask if user wants to search again
        printf("\nDo you want to search another contact?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &a);

    } while (a == 1); // repeat if user chooses Yes
}


