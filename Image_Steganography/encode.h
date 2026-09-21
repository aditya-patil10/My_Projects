#ifndef ENCODE_H
#define ENCODE_H

#include <stdio.h>
#include "types.h" // Contains user defined types

// Structure to store information required for
// encoding secret file to source Image.
// Information about output and intermediate data is also stored.

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 20

typedef struct _EncodeInfo
{
    char magic_string[20];

    // Source image info.
    char *src_image_fname;
    FILE *fptr_src_image;
    uint image_capacity;


    // Secret file info.
    char *secret_fname;
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX];
    long size_secret_file;

    // Stego image info.
    char *stego_image_fname;
    FILE *fptr_stego_image;

} EncodeInfo;

// Check operation type.
OperationType check_operation_type(char *argv[]);

// Read and validate encode arguments from argv.
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);
Status validate_secret_file_type(char *argv[], EncodeInfo *encInfo);

// Perform the encoding.
Status do_encoding(EncodeInfo *encInfo);

// Get file pointers for input and output files.
Status open_files_for_encoding(EncodeInfo *encInfo);

// Check capacity.
Status check_capacity(EncodeInfo *encInfo);

// Get image size.
uint get_image_size_for_bmp(FILE *fptr_image);

// Get file size.
uint get_file_size(FILE *fptr);

// Copy BMP image header.
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

void encode_int_image(char *arr, int data);

void encode_string_to_image(const char *str, int len, FILE *fptr_src_image, FILE *fptr_stego_image);

void encode_char_to_image(char *arr, char data);

Status encode_size_of_MS(EncodeInfo *encInfo);

// Store magic string.
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);

// Encode secret file extension.
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);

// Encode secret file size.
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo);

// Encode secret file data.
Status encode_secret_file_data(EncodeInfo *encInfo);

// Encode function, which does the real encoding.
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);

// Encode a byte into the LSB of image data array.
Status encode_byte_to_lsb(char data, char *image_buffer);

// Copy remaining image bytes from src to stego image after encoding.
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);

#endif
