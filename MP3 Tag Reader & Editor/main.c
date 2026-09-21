
#include <stdio.h>
#include <string.h>
#include"files.h"  

int main(int argc, char *argv[])
{
    if (argc < 2)  
    {
        printf("\nError : Invalid format!!\n");
        printf("Use : \"./a.out --help\" for Help menu.\n\n");
    }
    else if (argc == 2)  // Only 2 argument: ./a.out --help
    {
        if (strcmp(argv[1], "--help") == 0)  // Display help menu
        {
            printf("\nINFO : Help Menu for Tag Reader and Editor:\n\n");

            printf("For Displaying Content :\n");
            printf("./a.out -v <file_name.mp3>\n\n");

            printf("For Editing :\n");  
            printf("./a.out -e -t \"Enter_title\" <file_name.mp3>\n");
            printf("./a.out -e -y \"Enter_year\" <file_name.mp3>\n");
            printf("./a.out -e -a \"Enter_artist\" <file_name.mp3>\n");
            printf("./a.out -e -A \"Enter_album\" <file_name.mp3>\n");
            printf("./a.out -e -g \"Enter_content\" <file_name.mp3>\n");
            printf("./a.out -e -c \"Enter_comments\" <file_name.mp3>\n\n");
        }
        else  // Invalid single argument
        {
            printf("\nError : Invalid format!!\n");
            printf("Use : \"./a.out --help\" for Help menu.\n\n");
        }
    }
    else if (argc == 3)  // View mode: -v <file>
    {
        if (strcmp(argv[1], "-v") == 0)  // Check for view command
        {
            if (validate_view(argv[2]) == 0)  // Validate MP3 file
            {
                printf("Error!!");
                return 0;
            }

            view_data(argv[2]);  // Display MP3 tags
        }
        else  
        {
            printf("Invalid command!!\n");
            printf("Use : ./a.out -v \"file.mp3\"\n");
        }
    }
    else if (argc == 5)  // Edit mode: -e <option> <data> <file>
    {
        if (strcmp(argv[1], "-e") == 0)  // Check for edit command
        {
            if (validate_edit(argv[4]) == 0)  // Validate MP3 file
            {
                printf("Error!!");
                return 0;
            }

            edit_data(argv[2], argv[3], argv[4]);  // Edit specific tag
        }
        else  
        {
            printf("Invalid command!!\n");
            printf("Use: ./a.out -e <tag option> <new name> \"file.mp3\" \n");
        }
    }
    else  // Invalid number of arguments
    {
        printf("Error : Unsupported Operation.\n");
        printf("Use : \"./a.out --help\" for Help menu.\n\n");
    }
}