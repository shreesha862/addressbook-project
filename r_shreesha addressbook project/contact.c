#include "contact.h"
#include <string.h>
#include <ctype.h>

// Name validation
void name_validation(char *na)
{
    int flag;
    do 
    {
        printf("Enter the name: ");
        getchar();
        scanf("%[^\n]", na);

        flag = 1;//assumming it is crt at first

        //Rule 1: checking for the alphabets and the spaces
        for (int i = 0; na[i] != '\0'; i++) 
        {
            // If the character is not a letter and a space , mark the name invalid.
            if (isalpha(na[i])==0 && na[i]!=' ')
            {  
                flag = 0; //invalid
                break;
            }
        }
            
        // If the name is not valid, print an error message
        if (flag==0) 
        {
            printf("Invalid name! Only alphabets allowed.\n");
        }

    } while (flag==0);   // repeat until flag == 1
}

// Mobile validation
void mobile_validation(AddressBook *addressbook, char *mobile)
{
   int flag;
    do {
        printf("Enter the Mobile number: ");
        scanf("%s", mobile);

        flag = 1; //assuming that it is valid

        // Rule 1: checking the length 
        if (strlen(mobile) != 10) //length is checked
        {
            printf("Invalid mobile number! Must be 10 digits.\n");
            flag= 0; //valid initialized to zero if false
        } 
        if(flag==1)  //only checks if length is crt
        {
          
            //Rule 2: only digits from 0 to 9
        for (int i = 0; mobile[i]; i++)
        {
        if (!(mobile[i] >= '0' && mobile[i] <= '9')) //checking  only for the digits 
        {
        printf("Invalid mobile number! Only digits allowed.\n");
        flag = 0; //again initalize flag to zero if false
        break;
        }
        }
    }
    if(flag==1)//if length and digit is crt 
       {
           //  Rule 3: duplicate checks 
            for (int i = 0; i < addressbook->contact_count; i++) 
            {
                if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0) //compare with the structure of contact_detail of array
                {
                    printf("Mobile number already exists!\n");
                    flag= 0;
                    break;
                }
            }
        }
    } while (!flag);   // repeat until flag == 1
}

// Email validation
void email_validation(AddressBook *addressbook, char *email)
{
    int valid;
    do {
        printf("Enter the Mail ID: ");
        scanf(" %[^\n]", email);

        valid = 1; // assume valid initially

        // Rule 1: No spaces
        for (int i = 0; email[i] != '\0'; i++)
         {
            if (email[i] == ' ')
             {
                printf("Invalid email! Spaces are not allowed.\n");
                valid = 0;
                break;
            }
        }

        // Rule 2: Only lowercase letters, digits, '@', '.', and '_'
        if (valid == 1) 
        {
            for (int i = 0; email[i] != '\0'; i++)
             {
                if (!((email[i] >= 'a' && email[i] <= 'z') ||
                      (email[i] >= '0' && email[i] <= '9') ||
                      email[i] == '@' || email[i] == '.' || email[i] == '_')) 
                {
                    printf("Invalid email! Only lowercase letters, digits, '@', '.', and '_' allowed.\n");
                    valid = 0;
                    break;
                }
            }
        }

        // Rule 3: Must contain exactly one '@'
        if (valid == 1) 
        {
            int at_count = 0;
            for (int i = 0; email[i] != '\0'; i++) 
            {
                if (email[i] == '@') 
                 at_count++;
            }
            if (at_count != 1)
             {
                printf("Invalid email! Must contain exactly one '@'.\n");
                valid = 0;
            }
        }

        // Rule 4: '@' must not be first or last character
        if (valid == 1)
         {
            char *at_pos = strchr(email, '@');
            if (at_pos == email || at_pos == NULL || *(at_pos + 1) == '\0') 
            {
                printf("Invalid email! '@' cannot be at start or end.\n");
                valid = 0;
            }
        }

        // Rule 5: Must end with ".com"
        if (valid == 1) 
        {
            int len = strlen(email);
            if (len < 5 || strcmp(email + len - 4, ".com") != 0)
             {
                printf("Invalid email! Must end with '.com'.\n");
                valid = 0;
            }
        }

        // Rule 6: Duplicate check
        if (valid == 1) 
        {
            for (int i = 0; i < addressbook->contact_count; i++)
             {
                if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0) 
                {
                    printf("Email already exists!\n");
                    valid = 0;
                    break;
                }
            }
        }
        // Rule 7: Ensure domain part (after '@') is valid
       if (valid == 1) 
         {
        char *at_pos = strchr(email, '@');
         if (at_pos != NULL)
        {
         char *dot_pos = strstr(at_pos, ".com");
        // Check that ".com" exists and there are characters between '@' and '.'
        if (dot_pos == NULL || dot_pos == at_pos + 1)
        {
            printf("Invalid email! Must have domain name between '@' and '.com'.\n");
            valid = 0;
        }
       }
}
       // Rule 8: Email must start with a lowercase letter
        if (valid == 1)
        {
           if (!(email[0] >= 'a' && email[0] <= 'z')) 
         {
        printf("Invalid email! Must start with a lowercase letter.\n");
        valid = 0;
        }
        }



    } while (!valid); // repeat until valid == 1
}

//creating of the contacts
void create_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count >= 100) 
    {
        printf("Address book is full!\n");
        return; //if>=100
    }

    int a;  // control variable for loop
    do {
        if (addressbook->contact_count >= 100)
         {
            printf("Address book is full!\n");
            break;   // stop if full
        }

        // temporary variables for storing and comparing
        char na[20];
        char mobile[11];
        char email[30];

        // validation functions
        name_validation(na);
        mobile_validation(addressbook, mobile);
        email_validation(addressbook, email);

        // store into structure after passing all the validations
        Contacts *update = &addressbook->contact_details[addressbook->contact_count];
        strcpy(update->Name, na);
        strcpy(update->Mobile_number, mobile);
        strcpy(update->Mail_ID, email);

        // increment count
        addressbook->contact_count++;
        printf("Contact created successfully!\n");

        // Ask if user wants to add another
        printf("\nDo you want to add another contact?\n");
        printf("1. Yes\n2. No (Return to main menu)\n");
        scanf("%d", &a);

    } while (a== 1);
}

//saving of the contacts
void save_contacts(AddressBook *addressbook) 
{
    FILE *fp = fopen("contacts.csv", "w"); //creating and opening file in the write mode
    if (fp == NULL) //if it is null
    {
        printf("Error opening file for writing.\n");
        return;
    }
     
    fprintf(fp,"#%d\n",addressbook->contact_count);//printing to the file
   // take a loop to make the entry 
   for (int i = 0; i < addressbook->contact_count; i++)
  {
    Contacts *entry = &addressbook->contact_details[i];
    fprintf(fp, "%s,%s,%s\n", entry->Name, entry->Mobile_number, entry->Mail_ID);
  }
    fclose(fp); //close the file
    printf("Contacts saved successfully!\n");
}
//loading of the contacts
void load_contacts(AddressBook *addressbook) 
{
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL) //if found null
    {
        printf("No saved contacts found.\n");
        return;
    }

    // Read the count from the first line
    fscanf(fp, "#%d\n", &addressbook->contact_count); 
    //if count=0 means there r no 
    
    if (addressbook->contact_count == 0)
    {
        printf("No contacts to load.\n");
        fclose(fp);
        return;
    } 
    // Read each contact line
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
            fscanf(fp, "%[^,],%[^,],%[^\n]\n",
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);
    }
    fclose(fp); //close the file
    printf("Contacts loaded successfully!\n");
}







