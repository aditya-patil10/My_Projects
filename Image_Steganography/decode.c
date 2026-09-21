#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"

// Validate the decode command-line arguments.
// The input stego file must be a BMP, and the target output file name is optional.
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (strstr(argv[2], ".bmp") != NULL)
    {
        decInfo->stego_file = argv[2];
    }
    else
    {
        printf("\nError: Stego file is not a .bmp file\n");
        return e_failure;
    }

    if (argv[3] != NULL)
    {
        strncpy(decInfo->secret_fname, argv[3], sizeof(decInfo->secret_fname) - 1);

        decInfo->secret_fname[sizeof(decInfo->secret_fname) - 1] = '\0';
    }
    else
    {
        strcpy(decInfo->secret_fname, "output");
    }

    return e_success;
}

// Open the stego image so the hidden payload can be extracted from its LSBs.
Status open_files_for_decoding(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_file, "rb");

    if (decInfo->fptr_stego_image == NULL)
    {
        printf("\nError: Unable to open stego image file %s\n", decInfo->stego_file);
        return e_failure;
    }

    return e_success;
}

// Skip the 54-byte BMP header because the hidden payload begins after the header.
Status skip_header_file(DecodeInfo *decodeinfo)
{
    fseek(decodeinfo->fptr_stego_image, 54, SEEK_CUR);
    return e_success;
}

// Reconstruct an integer from 32 LSB bits stored in the image.
int decode_int_from_lsb_image(char *arr)
{
    int data = 0;
    int bit;

    // Read 32 hidden bits and rebuild the original integer value.
    for (int i = 0; i < 32; i++)
    {
        bit = arr[i] & 1;
        data = (data << 1) | bit;
    }

    return data;
}

// Read the hidden metadata size for the magic string before decoding it.
Status decode_size_magic_string(DecodeInfo *decodeinfo)
{
    char arr[32];
    fread(arr, 32, 1, decodeinfo->fptr_stego_image);

    decodeinfo->size_magic_string = decode_int_from_lsb_image(arr);
    if (decodeinfo->size_magic_string <= 0 ||
        decodeinfo->size_magic_string >= 100)
    {
        printf("\nInvalid magic string size\n");
        return e_failure;
    }

    return e_success;
}

// Rebuild one character from 8 LSB bits stored in the image.
char decode_string_from_lsb_image(char *arr)
{
    char data = 0;
    int bit;

    for (int i = 0; i < 8; i++)
    {
        bit = arr[i] & 1;
        data = (data << 1) | bit;
    }

    return data;
}

// Recover the magic string from the image and compare it with the user-provided
// value to confirm that the file has not been tampered with.
Status decode_magic_string(DecodeInfo *decodeinfo)
{

    char arr[8];
    char decoded_magic_string[100];
    if (decodeinfo->size_magic_string <= 0 ||
        decodeinfo->size_magic_string >= (int)sizeof(decoded_magic_string))
    {
        printf("\nInvalid magic string size\n");
        return e_failure;
    }

    for (int i = 0; i < decodeinfo->size_magic_string; i++)
    {

        fread(arr, 8, 1, decodeinfo->fptr_stego_image);
        decoded_magic_string[i] = decode_string_from_lsb_image(arr);
    }
    decoded_magic_string[decodeinfo->size_magic_string] = '\0';

    printf("Enter Magic String to Varify : ");
    scanf(" %99[^\n]", decodeinfo->magic_string);
    if (strcmp(decodeinfo->magic_string, decoded_magic_string) != 0)
    {
        printf("\nMagic String is Not Matching!\n");
        return e_failure;
    }

    return e_success;
}

// Read the size of the hidden file extension before extracting its name.
Status decode_size_of_extension(DecodeInfo *decodeinfo)
{

    char arr[32];
    fread(arr, 32, 1, decodeinfo->fptr_stego_image);
    decodeinfo->size_of_extension = decode_int_from_lsb_image(arr);
    if (decodeinfo->size_of_extension <= 0 ||
        decodeinfo->size_of_extension >= 100)
    {
        printf("Invalid extension size\n");
        return e_failure;
    }

    return e_success;
}

/*Reconstruct the original secret file extension and append it to the output
filename so the restored file has a proper type.*/
Status decode_extension(DecodeInfo *decodeinfo)
{
    char arr[8];
    char extension[100];

    if (decodeinfo->size_of_extension <= 0 || decodeinfo->size_of_extension >= sizeof(extension))
    {
        printf("Invalid extension size\n");
        return e_failure;
    }

    for (int i = 0; i < decodeinfo->size_of_extension; i++)
    {
        fread(arr, 1, 8, decodeinfo->fptr_stego_image);

        extension[i] = decode_string_from_lsb_image(arr);
    }

    extension[decodeinfo->size_of_extension] = '\0';

    strcat(decodeinfo->secret_fname, extension);

    return e_success;
}

// Read the size of the hidden payload before extracting the actual secret bytes.
Status decode_data_size(DecodeInfo *decodeinfo)
{

    char arr[32];
    fread(arr, 32, 1, decodeinfo->fptr_stego_image);
    decodeinfo->data_size = decode_int_from_lsb_image(arr);
    return e_success;
}

// Extract the payload byte by byte and write it into the recovered secret file.
Status decode_data(DecodeInfo *decodeinfo)
{
    char arr[8];
    char ch;

    for (int i = 0; i < decodeinfo->data_size; i++)
    {
        if (fread(arr, 1, 8, decodeinfo->fptr_stego_image) != 8)
        {
            return e_failure;
        }

        ch = decode_string_from_lsb_image(arr);

        if (fwrite(&ch, 1, 1, decodeinfo->output_file) != 1)
        {
            return e_failure;
        }
    }

    return e_success;
}

/*Main decode flow:
1. open the stego image
2. skip the BMP header
3. read the hidden metadata
4. verify the magic string
5. rebuild the extension and output file name
6. extract the secret data into the output file*/

/*It reads the metadata in the same order used during encoding, verifies the
magic string, and finally rebuilds the secret file from the embedded bits.*/

Status do_decoding(DecodeInfo *decInfo)
{
    // Open the stego image and reconstruct the hidden file metadata in order.
    if (open_files_for_decoding(decInfo) == e_failure)
    {
        printf("\nError: Failed to open stego image\n");
        return e_failure;
    }

    printf("\nFile opened successfully\n");

    skip_header_file(decInfo);

    if (decode_size_magic_string(decInfo) == e_failure)
    {
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    if (decode_magic_string(decInfo) == e_failure)
    {
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    if (decode_size_of_extension(decInfo) == e_failure)
    {
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    if (decode_extension(decInfo) == e_failure)
    {
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    if (decode_data_size(decInfo) == e_failure)
    {
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    decInfo->output_file = fopen(decInfo->secret_fname, "wb");

    if (decInfo->output_file == NULL)
    {
        perror("fopen");
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    if (decode_data(decInfo) == e_failure)
    {
        fclose(decInfo->output_file);
        fclose(decInfo->fptr_stego_image);
        return e_failure;
    }

    fclose(decInfo->output_file);
    fclose(decInfo->fptr_stego_image);

    printf("\nSecret File Decoded Successfully : %s\n\n", decInfo->secret_fname);

    return e_success;
}