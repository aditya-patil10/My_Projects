#include "contact.h"
#include <stdio.h>
#include <string.h>

//To check the given Name is valid or not.
int validate_name(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              str[i] == ' ' ||
              str[i] == '.'))
        {

            printf("Invalid name!!\n");
            return 0;
        }
    }

    return 1;
}

//To check the given Phone no. is valid or not.
int validate_phone(AddressBook *addressBook, char *str)
{
    if (strlen(str) != 10)
    {
        printf("Phone number must contain 10 digits.\n");
        return 0;
    }

    for (int i = 0; str[i]; i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("Phone number must contain only digits.\n");
            return 0;
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            printf("Phone number already exists.\n");
            return 0;
        }
    }

    return 1;
}

//To check the given Email is valid or not.
int validate_email(AddressBook *addressBook, char *str)
{
    int at_count = 0, at_pos = -1, dot_count = 0, dot_pos = -1;
    int len = strlen(str);

    if (len < 5)
    {
        return 0; // s@g.c
    }

    if (!(str[0] >= 'a' && str[0] <= 'z'))
    {
        printf("Email must start with a lowercase letter\n");
        return 0;
    }

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '@')
        {
            at_pos = i;
            at_count++;
        }
    }

    //in email there should be only 1 @
    if ((at_pos < 1) || (at_count != 1))
    {
        printf("Invalid email id!!\n");
        return 0;
    }

    for (int i = at_pos; str[i]; i++)
    {
        if (str[i] == '.')
        {
            dot_pos = i;
            dot_count++;
        }
        else if (!((str[i] >= 'a' && str[i] <= 'z') ||
                   (str[i] >= '0' && str[i] <= '9') ||
                   str[i] == '.' || str[i] == '_' ||
                   str[i] == '-' || str[i] == '@'))
        {
            printf("Invalid email format!!\n");
            return 0;
        }
    }

    if ((dot_pos == -1) || (dot_pos == len - 1) || (dot_count != 1) || (dot_pos == at_pos + 1))
    {
        return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, str) == 0)
        {
            printf("Email already exists\n");
            return 0;
        }
    }

    return 1;
}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];

    printf("Enter the phone number: ");
    scanf("%10s", str);


    printf("-------------------------------------------------------------------------------\n");
    printf("|                               CONTACT FOUND!!                               |\n");
    printf("*******************************************************************************\n");
    printf("| %-5s | %-25s | %-10s | %-25s |\n", "Sr.No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(str, addressBook->contacts[i].phone) == 0)
        {
            printf("|  %-5d | %-25s | %-10s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);


            return i;
        }
    }
    printf("-------------------------------------------------------------------------------\n");

    printf("Contact not found!!!!\n");
    return -1;
}

int search_by_name(AddressBook *addressBook)
{
    char str[30];
    int count = 0;
    int index;

    printf("Enter the name: ");
    scanf(" %[^\n]", str);

    printf("-------------------------------------------------------------------------------\n");
    printf("|                              CONTACT FOUND!!                               |\n");
    printf("*******************************************************************************\n");
    printf("| %-5s | %-25s | %-10s | %-25s |\n", "Sr.No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(str, addressBook->contacts[i].name) == 0)
        {
            printf("| %-5d | %-25s | %-10s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);

            count++;
            index = i;
        }
    }
    printf("-------------------------------------------------------------------------------\n");

    if (count == 0)
    {
        printf("Contact not found!!!!\n");
        return -1;
    }

    if (count > 1)
    {
        printf("\nMultiple contacts found with this name!!\n");
        printf("Search using phone number.\n");

        return search_by_phone(addressBook);
    }

    return index;
}

int search_by_email(AddressBook *addressBook)
{
    char str[30];

    printf("Enter the email: ");
    scanf(" %[^\n]", str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(str, addressBook->contacts[i].email) == 0)
        {
            return i;
        }
    }

    printf("Contact not found\n");
    return -1;
}