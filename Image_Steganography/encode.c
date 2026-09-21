#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "encode.h"
#include "types.h"

// Function definitions

// Validate that the secret file has a supported extension before embedding it.
// Only a small set of media formats are accepted by this project.
Status validate_secret_file_type(char *argv[], EncodeInfo *encInfo)
{
    char *extension;

    extension = strrchr(argv[3], '.');

    if (extension == NULL)
    {
        printf("The secret file type is not supported\n");
        return e_failure;
    }

    if (strcmp(extension, ".txt") == 0 ||
        strcmp(extension, ".mp3") == 0 ||
        strcmp(extension, ".jpeg") == 0 ||
        strcmp(extension, ".png") == 0 ||
        strcmp(extension, ".mp4") == 0)
    {
        encInfo->secret_fname = argv[3];

        strcpy(encInfo->extn_secret_file, extension);

        return e_success;
    }

    printf("The secret file type is not supported\n");
    return e_failure;
}

// Read and validate command-line arguments for the encoding mode.

/*The source image must be a BMP file, and the output stego image can be
either user-provided or set to a default name.*/

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    if (strstr(argv[2], ".bmp") != NULL)
    {
        encInfo->src_image_fname = argv[2];
    }
    else
    {
        printf("\nError : It is not a .bmp file\n");
        return e_failure;
    }

    if (validate_secret_file_type(argv, encInfo) != e_success)
    {
        return e_failure;
    }

    if (argv[4] != NULL)
    {
        if (strstr(argv[4], ".bmp") != NULL)
        {
            encInfo->stego_image_fname = argv[4];
        }
        else
        {
            printf("\nError : It is not a .bmp file\n");
            return e_failure;
        }
    }
    else
    {
        encInfo->stego_image_fname = "stego.bmp";
    }

    // Get secret file extension.
    char *extension = strrchr(encInfo->secret_fname, '.');

    if (extension != NULL)
    {
        strcpy(encInfo->extn_secret_file, extension);
    }
    else
    {
        strcpy(encInfo->extn_secret_file, "");
    }

    return e_success;
}

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;

    // BMP stores width and height near byte 18.
    fseek(fptr_image, 18, SEEK_SET);

    // Read image dimensions and estimate how many pixel bytes are available.
    fread(&width, sizeof(int), 1, fptr_image);
    fread(&height, sizeof(int), 1, fptr_image);

    rewind(fptr_image);
    return width * height * 3; // 3 bytes per pixel (RGB)
}

// Open all required files for encoding:
// - source BMP image
// - secret file to hide
// - destination stego image
Status open_files_for_encoding(EncodeInfo *encInfo)
{
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");

    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        printf("Error: Unable to open source image!!\n");

        return e_failure;
    }

    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");

    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        printf("Error: Unable to open secret file!!\n");

        fclose(encInfo->fptr_src_image);
        return e_failure;
    }

    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");

    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        printf("Error: Unable to open stego image!!\n");

        fclose(encInfo->fptr_src_image);
        fclose(encInfo->fptr_secret);

        return e_failure;
    }

    return e_success;
}

/*Check whether the image has enough space to hide:
- magic string size
- file extension size
- secret file size
- actual secret data bits*/

Status check_capacity(EncodeInfo *encInfo)
{
    long secret_file_size;
    long required_size;

    // Measure the secret file so we know how many bits must be hidden.
    fseek(encInfo->fptr_secret, 0, SEEK_END);

    secret_file_size = ftell(encInfo->fptr_secret);

    rewind(encInfo->fptr_secret);

    encInfo->size_secret_file = secret_file_size;

    /*Required bits:
    Magic string size       = 32 bits
    Magic string            = magic string characters * 8
    Secret extension        = extension characters * 8
    Secret file size        = 32 bits
    Secret data             = file size * 8*/

    required_size = 32 + (strlen(encInfo->magic_string) * 8) +
        (strlen(encInfo->extn_secret_file) * 8) + 32 + (secret_file_size * 8);

    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    if (required_size <= encInfo->image_capacity)
    {
        return e_success;
    }

    return e_failure;
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char header[54];

    // Keep the original BMP file header so the stego image stays valid.
    fread(header, 1, 54, fptr_src_image);
    fwrite(header, 1, 54, fptr_stego_image);

   //printf("BMP header copied successfully!!\n");

    return e_success;
}

// Store the length of the magic string in the first 32 hidden bits.
// This lets the decoder know how many bytes to read while reconstructing it.
Status encode_size_of_MS(EncodeInfo *encInfo)
{
    int size = strlen(encInfo->magic_string);

    char arr[32];
    fread(arr, 1, 32, encInfo->fptr_src_image);

    encode_int_image(arr, size);

    fwrite(arr, 1, 32, encInfo->fptr_stego_image);

    return e_success;
}

// Embed the magic string into the image after the size field.
// The decoder will verify this string to confirm the stego image was built
// using the same encoding scheme.
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    encode_string_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image);
    return e_success;
}

// Write the secret file extension metadata before the hidden payload itself.
// Example: .txt, .png, .mp3
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char arr[32];
    int extension_size;

    extension_size = strlen(file_extn);

    fread(arr, 1, 32, encInfo->fptr_src_image);

    encode_int_image(arr, extension_size);

    fwrite(arr, 1, 32, encInfo->fptr_stego_image);

    encode_string_to_image(file_extn, extension_size, encInfo->fptr_src_image, encInfo->fptr_stego_image);

    return e_success;
}

/*Store the original secret file size in 32 bits so the decoder knows how many
bytes of hidden data must be recovered.*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char arr[32];

    fread(arr, 1, 32, encInfo->fptr_src_image);

    encode_int_image(arr, file_size);
    
    fwrite(arr, 1, 32, encInfo->fptr_stego_image);

    return e_success;
}

/* Read the secret file into memory and embed its bytes one by one into the
 least significant bits of the image data.*/
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char *data;

    data = malloc(encInfo->size_secret_file);

    if (data == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return e_failure;
    }

    rewind(encInfo->fptr_secret);

    if (fread(data, sizeof(char), encInfo->size_secret_file, encInfo->fptr_secret) != encInfo->size_secret_file)
    {
        printf("Error: Unable to read secret file\n");
        free(data);
        return e_failure;
    }

    encode_data_to_image(data, encInfo->size_secret_file, encInfo->fptr_src_image, encInfo->fptr_stego_image);
    free(data);

    return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char ch;

    while (fread(&ch, sizeof(char), 1, fptr_src_image) == 1)
    {
        fwrite(&ch, sizeof(char), 1, fptr_stego_image);
    }

    return e_success;
}

Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    encode_string_to_image(data, size, fptr_src_image, fptr_stego_image);

    return e_success;
}

/* Hide a string by replacing the LSB of each byte in the image with one bit of
the character data. Each character requires 8 bits.*/
void encode_string_to_image(const char *str, int len, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    int i;
    char arr[8];

    for (i = 0; i < len; i++)
    {
        fread(arr, sizeof(char), 8, fptr_src_image);

        encode_char_to_image(arr, str[i]);

        fwrite(arr, sizeof(char), 8, fptr_stego_image);
    }
}

// Encode one byte by modifying only the least significant bits of 8 image bytes.
// This is the core of the LSB-based steganography technique.
void encode_char_to_image(char *arr, char data)
{
    // Replace each LSB in the 8-byte block with one bit from the secret byte.
    for (int i = 0; i < 8; i++)
    {
        arr[i] = arr[i] & (~1);
        int get_bit = (data >> (7 - i)) & 1;
        arr[i] = arr[i] | get_bit;
    }
}

// Encode an integer into 32 bits by storing each bit in the LSB of a byte.
// This is used for lengths and sizes in the hidden metadata.
void encode_int_image(char *arr, int data)
{
    for (int i = 0; i < 32; i++)
    {
        arr[i] = arr[i] & (~1);
        int get_bit = (data >> (31 - i)) & 1;
        arr[i] = arr[i] | get_bit;
    }
}

// Main encoding routine.
/*It writes the metadata first, then the hidden secret data, and finally copies
the remaining original image bytes to preserve the visual image.*/
Status do_encoding(EncodeInfo *encInfo)
{
    // Open the source image, secret file, and output image before hiding data.
    if (open_files_for_encoding(encInfo) == e_failure)
    {
        printf("Error: Failed to open files\n");
        return e_failure;
    }
    else
    {
        printf("\nFiles opened successfully!!\n");
    }

    printf("Enter the magic string to be encoded: ");
    scanf(" %[^\n]", encInfo->magic_string);

    if (check_capacity(encInfo) == e_failure)
    {
        printf("Error: Insufficient capacity in the image\n");
        fclose(encInfo->fptr_src_image);
        fclose(encInfo->fptr_secret);
        fclose(encInfo->fptr_stego_image);

        return e_failure;
    }

    if (copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        return e_failure;
    }

    if (encode_size_of_MS(encInfo) == e_failure)
    {
        return e_failure;
    }

    if (encode_magic_string(encInfo->magic_string, encInfo) == e_failure)
    {
        return e_failure;
    }

    if (encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_failure)
    {
        printf("Error: Failed to encode secret file extension\n");
        return e_failure;
    }

    if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_failure)
    {
        printf("Error: Failed to encode secret file size\n");
        return e_failure;
    }

    if (encode_secret_file_data(encInfo) == e_failure)
    {
        printf("Error: Failed to encode secret file data\n");
        return e_failure;
    }

    if (copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        printf("Error: Failed to copy remaining image data\n");
        return e_failure;
    }

    printf("\nThe Output File is : %s\n",encInfo->stego_image_fname);
    fclose(encInfo->fptr_src_image);
    fclose(encInfo->fptr_secret);
    fclose(encInfo->fptr_stego_image);

    printf("Data Encoding completed successfully..!\n\n");

    return e_success;
}
