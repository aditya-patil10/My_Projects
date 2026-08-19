/**Name - Aditya S. Patil (26015_022).
 *Date - 05/08/2026 to 09/08/2026
 *Description : The Address Book Management System is a menu-driven C program designed to store
            and manage up to 100 contacts efficiently. It allows users to create, search, edit, 
            delete, and display contact information. The program also provides file handling 
            functionality to save the contacts permanently and load them when required.
 *Key Features :
 -> Stores up to 100 contacts.
 -> Provides a simple menu-driven interface.
 -> Supports Create, Search, Edit, Delete, and List operations.
 -> Uses file handling to store contact data permanently.
 -> Provides easy and organized contact management.*/

#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;

    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("\n\n***************************************\n");
        printf("|        YOUR ADDRESS BOOK MENU       |\n");
        printf("---------------------------------------\n");
        printf("|   1   |   %-25s |\n", "CREATE CONTACT");
        printf("|   2   |   %-25s |\n", "SEARCH CONTACT");
        printf("|   3   |   %-25s |\n", "EDIT CONTACT");
        printf("|   4   |   %-25s |\n", "DELETE CONTACT");
        printf("|   5   |   %-25s |\n", "LIST ALL CONTACTS");
        printf("|   6   |   %-25s |\n", "SAVE AND EXIT");
        printf("---------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("Saving and Exiting...\n");
            saveContactsToFile(&addressBook);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
