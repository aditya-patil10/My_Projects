#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");

    fprintf(fp, "#%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%25s, %10s, %25s\n",
                addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fc = fopen("contacts.csv", "r");

    if (ferror(fc))
    {
        printf("Error occurred!!\n");
    }

    if (fc == NULL)
    {
        printf("Can't accesse file contacts.csv\n");
        return;
    }

    fscanf(fc, "#%d\n", &addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fc, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fc);
}
