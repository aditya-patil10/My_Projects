// Implementation of stack using array

#include <stdio.h>

int main()
{
    int arr[100];
    int op, size = 0;
    int data, i, found;

    do
    {
        printf("\nEnter the Option:\n");
        printf("1. Insertion\n2. Delete\n3. Print\n4. Search\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            if (size >= 100)
            {
                printf("Array is Full\n");
            }
            else
            {
                printf("Enter the element: ");
                scanf("%d", &data);

                arr[size++] = data;
                printf("Insertion complete\n");
            }
            break;

        case 2:
            if (size <= 0)
            {
                printf("Array is Empty\n");
            }
            else
            {
                printf("Deleted element: %d\n", arr[size - 1]);
                size--;
            }
            break;

        case 3:
            if (size <= 0)
            {
                printf("Array is Empty\n");
            }
            else
            {
                printf("Stack elements are:\n");
                for (i = size - 1; i >= 0; i--)
                {
                    printf("%d\n", arr[i]);
                }
            }
            break;

        case 4:
            if (size <= 0)
            {
                printf("Array is Empty\n");
            }
            else
            {
                printf("Enter element to search: ");
                scanf("%d", &data);

                found = 0;

                for (i = size - 1; i >= 0; i--)
                {
                    if (arr[i] == data)
                    {
                        printf("%d found in stack.\n", data);
                        found = 1;
                        break;
                    }
                }

                if (found == 0)
                {
                    printf("%d not found in stack.\n", data);
                }
            }
            break;

        case 5:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid Option\n");
        }

    } while (op != 5);

    return 0;
}