// Standard library includes for file I/O, string operations, and memory allocation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "files.h"  // Custom header with function declarations

// Convert unsigned int to Little-endian byte order (4 bytes)
void LtoB_endian(unsigned int new_size, unsigned char *size_of_tag)
{
    size_of_tag[0] = (new_size >> 24) & 0xFF;  // Most significant byte
    size_of_tag[1] = (new_size >> 16) & 0xFF;
    size_of_tag[2] = (new_size >> 8) & 0xFF;
    size_of_tag[3] = new_size & 0xFF;  // Least significant byte
}

// Check if file is valid for editing (must be .mp3 file)
int validate_edit(char *file)
{
    if (file == NULL)  // Check if filename exists
        return 0;

    if (strstr(file, ".mp3") == NULL)  // Check if file has .mp3 extension
    {
        printf("Invalid song file!!\n");
        return 0;
    }

    return 1;  // File is valid
}

// Edit ID3 tag fields in MP3 file
int edit_data(char *option, char *new_data, char *file)
{
    FILE *fp = fopen(file, "rb");  // Open file in read mode

    if (fp == NULL)  // Check if file opened successfully
    {
        printf("The file can't be opened!\n");
        return 0;
    }

    // Read 10-byte ID3 header
    unsigned char header[10];
    if (fread(header, 1, 10, fp) != 10)
    {
        printf("Invalid MP3 file!\n");
        fclose(fp);
        return 0;
    }

    char tag_to_edit[5];  // Store the ID3 frame name to edit

    // Map command-line options to ID3 frame identifiers
    if (strcmp(option, "-t") == 0)  // Title
    {
        strcpy(tag_to_edit, "TIT2");
    }
    else if (strcmp(option, "-y") == 0)  // Year
    {
        strcpy(tag_to_edit, "TYER");
    }
    else if (strcmp(option, "-a") == 0)  // Artist
    {
        strcpy(tag_to_edit, "TPE1");
    }
    else if (strcmp(option, "-A") == 0)  // Album
    {
        strcpy(tag_to_edit, "TALB");
    }
    else if (strcmp(option, "-g") == 0)  // Genre
    {
        strcpy(tag_to_edit, "TCON");
    }
    else if (strcmp(option, "-c") == 0)  // Comment
    {
        strcpy(tag_to_edit, "COMM");
    }
    else
    {
        printf("Invalid edit option!!!\n");
        fclose(fp);
        return 0;
    }

    // Create temporary file to write modified content
    FILE *temp = fopen("temp.mp3", "wb");

    if (temp == NULL)  // Check if temp file created
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return 0;
    }

    fwrite(header, 1, 10, temp);  // Copy ID3 header to temp file

    // Loop through all ID3 frames
    while (1)
    {
        // Read 4-byte frame identifier
        char tag_id[5];
        if (fread(tag_id, 1, 4, fp) != 4)
        {
            break;  // End of frames
        }
        tag_id[4] = '\0';  // Null-terminate string

        if (tag_id[0] == '\0')  // Empty tag = end of frames
        {
            break;
        }

        unsigned char tag_size[4];

        if (fread(tag_size, 1, 4, fp) != 4)  // Read frame size
        {
            break;
        }

        unsigned int new_size = BtoL_endian(tag_size);  // Convert byte order

        // Read frame flags (2 bytes)
        char flag[2];
        fread(flag, 1, 2, fp);

        // Read text encoding byte (0=ISO-8859-1, 1=UTF-16, etc.)
        unsigned char encoded;
        fread(&encoded, 1, 1, fp);

        if (new_size > 0)  // Subtract encoding byte from size
            new_size--;

        char *data = malloc(new_size+1);  // Allocate memory for frame data
        if(data == NULL)  // Check allocation success
        {
            fclose(fp);
            fclose(temp);
            remove("temp.mp3");
            return 0;
        }

        fread(data, 1, new_size, fp);  // Read frame data
        data[new_size]='\0';  // Null-terminate

        if(strcmp(tag_id, tag_to_edit)==0)  // If this is the frame to edit
        {
            fwrite(tag_id, 1, 4, temp);  // Write frame ID

            unsigned int new_tag_size=strlen(new_data)+1;  // Size of new data

            unsigned char new_size_int[4];
            LtoB_endian(new_tag_size,new_size_int);  // Convert to bytes

            fwrite(new_size_int,1,4,temp);  // Write new size
            fwrite(flag,1,2,temp);  // Write flags

            encoded=0;  // Set encoding to ISO-8859-1
            fwrite(&encoded,1,1,temp);
            
            // Write new tag value
            fwrite(new_data,1,strlen(new_data),temp);
        }
        else  // Frame not being edited, copy as-is
        {
            fwrite(tag_id,1,4,temp);
            fwrite(tag_size,1,4,temp);
            fwrite(flag,1,2,temp);
            fwrite(&encoded,1,1,temp);
            fwrite(data,1,new_size,temp);
        }
        free(data);  // Free allocated memory

        if(strcmp(tag_id,"COMM")==0)  // Stop after COMM frame
        {
            break;
        }
    }

int ch;

    // Copy remaining audio data from original to temp file
    while ((ch=fgetc(fp))!=EOF)
    {
        fputc(ch,temp);
    }
    
    // Close both files
    fclose(fp);
    fclose(temp);

    // Replace original file with modified temporary file
    remove(file);
    rename("temp.mp3",file);

    printf("Tag Edited Successufly\n");  // Notify user of success
    return 0;  // Return success
}