#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    //To save the contacts to the file.
    saveContactsToFile(addressBook);
    printf("Contacts saved successfully!!\n");

    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    char str[30], str1[11], str2[30];
    int res;

    do
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", str);

        res = validate_name(str);

    } while (res == 0);

    do
    {
        printf("Enter the phone: ");
        scanf(" %s", str1);

        res = validate_phone(addressBook, str1);

    } while (res == 0);

    do
    {
        printf("Enter the email: ");
        scanf(" %s", str2);

        res = validate_email(addressBook, str2);

    } while (res == 0);

    strcpy(addressBook->contacts[addressBook->contactCount].name, str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str2);

    addressBook->contactCount++;

    printf("\nContact created successfully!!!\n");
}

int searchContact(AddressBook *addressBook)
{
    int choice;

    printf("***************************************\n");
    printf("|             SEARCH MODE             |\n");
    printf("---------------------------------------\n");
    printf("|   1   |   %-25s |\n", "SEARCH BY NAME ");
    printf("|   2   |   %-25s |\n", "SEARCH BY PHONE");
    printf("|   3   |   %-25s |\n", "SEARCH BY EMAIL");
    printf("---------------------------------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        return search_by_name(addressBook);

    case 2:
        return search_by_phone(addressBook);

    case 3:
        return search_by_email(addressBook);

    default:
        printf("Invalid choice\n");
        return -1;
    }
}

void editContact(AddressBook *addressBook)
{
    int index;
    int choice;
    char str[30], str1[11], str2[30];

    index = searchContact(addressBook);

    if (index == -1)
    {
        return;
    }

    printf("***************************************\n");
    printf("|       WHAT YOU WANT TO EDIT ??      |\n");
    printf("---------------------------------------\n");
    printf("|   1   |   %-25s |\n", "NAME ");
    printf("|   2   |   %-25s |\n", "PHONE");
    printf("|   3   |   %-25s |\n", "EMAIL");
    printf("---------------------------------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        do
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", str);
        } while (validate_name(str) == 0);

        strcpy(addressBook->contacts[index].name, str);
        break;

    case 2:
        do
        {
            printf("Enter new phone number: ");
            scanf("%s", str1);
        } while (validate_phone(addressBook, str1) == 0);

        strcpy(addressBook->contacts[index].phone, str1);
        break;

    case 3:
        do
        {
            printf("Enter new email: ");
            scanf("%s", str2);
        } while (validate_email(addressBook, str2) == 0);

        strcpy(addressBook->contacts[index].email, str2);
        break;

    default:
        printf("Invalid choice\n");
        return;
    }

    printf("Contact edited successfully\n");
}

void deleteContact(AddressBook *addressBook)
{
    int index;
    int choice;

    index = searchContact(addressBook);

    if (index == -1)
    {
        return;
    }

    printf("\nDo you want to delete this contact?\n");
    printf("1. Yes\n2. No\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 2)
    {
        printf("Delete cancelled\n");
        return;
    }

    if (choice != 1)
    {
        printf("Invalid choice\n");
        return;
    }

    // Move all contacts one position backward
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}

void listContacts(AddressBook *addressBook)
{
    Contact temp;

    // Bubble sorting using names.
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0)
            {

                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    if (addressBook->contactCount == 0)
    {
        printf("No contacts available\n");
        return;
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("|                                ADDRESS BOOK                                 |\n");
    printf("*******************************************************************************\n");
    printf("| %-5s | %-25s | %-10s  | %-25s |\n", "Sr.No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-5d | %-25s | %-10s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-------------------------------------------------------------------------------\n");
}