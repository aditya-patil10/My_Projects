// Standard libraries for I/O, string operations, and memory allocation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"files.h"  // Custom header with function declarations

// Convert Big-endian (4 bytes) to unsigned integer
unsigned int BtoL_endian(unsigned char *size_of_tag)
{
    // Shift and combine bytes: MSB first to LSB last
    return ((unsigned int)size_of_tag[0] << 24) |
           ((unsigned int)size_of_tag[1] << 16) |
           ((unsigned int)size_of_tag[2] << 8) |
           (unsigned int)size_of_tag[3];
}

// Check if file is valid for viewing (must be .mp3 file)
int validate_view(char *file)
{
    if(file == NULL)  // Check if filename exists
    return 0;

    if (strstr(file, ".mp3") == NULL)  // Check if file has .mp3 extension
    {
        printf("Invalid song file!!\n");
        return 0;
    }

    return 1;  // File is valid
}

// Read and display MP3 ID3 tags
int view_data(char *file)
{
    FILE *fp = fopen(file, "rb");  // Open file in read mode

    if (fp == NULL)  // Check if file opened successfully
    {
        printf("The file can't be opened!\n");
        return 0;
    }

    // Read ID3 identifier (3 bytes: "ID3")
    char id[4];
    if (fread(id, 1, 3, fp) != 3)
    {
        printf("Invalid MP3 file!\n");
        fclose(fp);
        return 0;
    }
    id[3] = '\0';  // Null-terminate

    if (strcmp(id, "ID3") != 0)  // Check if ID3 tag exists
    {
        printf("ID3 tag not found\n");
        fclose(fp);
        return 0;
    }

    // Read ID3 version (2 bytes: major and minor version)
    unsigned char version[2];
    if (fread(version, 1, 2, fp) != 2)
    {
        printf("Invalid ID3 header!\n");
        fclose(fp);
        return 0;
    }

    printf("\n----------------------------------------------\n");
    printf("          MP3 TAG READER\n");
    printf("----------------------------------------------\n");
    printf("ID3 Version : v2.%d.%d\n", version[0], version[1]);

    fseek(fp, 5, SEEK_CUR); // Skip 5 bytes (flags and tag size)

    // Loop through all ID3 frames
    while (1)
    {
        // Read 4-byte frame identifier (e.g., "TIT2", "TYER")
        char tag_id[5];
        if (fread(tag_id, 1, 4, fp) != 4)
        {
            break;
        }
        tag_id[4] = '\0';

        if (tag_id[0] == '\0')  // Empty tag = end of frames
        {
            break;
        }

        // Read 4-byte frame size
        unsigned char size_of_tag[4];
        if (fread(size_of_tag, 1, 4, fp) != 4)
        {
            break;
        }

        unsigned int new_size = BtoL_endian(size_of_tag);  // Convert byte order

        fseek(fp, 2, SEEK_CUR); // Skip 2 bytes of frame flags

        char *contant = malloc(new_size + 1);  // Allocate memory for frame data

        if(contant == NULL)  // Check allocation success
        {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return 0;
        }

        // Read frame contents
        fread(contant, 1, new_size, fp);
        contant[new_size]='\0';
        
        // Match frame ID and display corresponding tag
        if(strcmp(tag_id, "TIT2")==0)
        {
            printf("Title       : %s\n",contant+1);  // Title
        }
        if(strcmp(tag_id, "TYER")==0)
        {
            printf("Year        : %s\n",contant+1);  // Year
        }
        if(strcmp(tag_id, "TPE1")==0)
        {
            printf("Artist      : %s\n",contant+1);  // Artist
        }
        if(strcmp(tag_id, "TALB")==0)
        {
            printf("Album       : %s\n",contant+1);  // Album
        }
        if(strcmp(tag_id, "TCON")==0)
        {
            printf("Genre       : %s\n",contant+1);  // Genre
        }
        if(strcmp(tag_id, "COMM")==0)
        {
            printf("Comments    : %s\n",contant+1);  // Comments
        }

        free(contant);  // Free allocated memory     
    }
    printf("----------------------------------------------\n");

    fclose(fp);  // Close file

    return 1;  // Return success
}