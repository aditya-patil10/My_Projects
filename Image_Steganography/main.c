#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

OperationType check_operation_type(char *argv[])
{
    // Decide whether the user wants to hide data or recover it.
    if (strcmp(argv[1], "-e") == 0)
        return e_encode;
    else if (strcmp(argv[1], "-d") == 0)
        return e_decode;
    else
        return e_unsupported;
}

int main(int argc, char *argv[])
{
    // Show usage when the command is missing required arguments.
    if (argc < 2)
    {
        printf("\nError: Invalid arguments\n");
        printf("Please use this Commands :\n");
        printf("For Encoding -> ./a.out -e <src_image.bmp> <secret_file.ext> <stego_image.bmp>\n");
        printf("For Decoding -> ./a.out -d <stego_image.bmp> <secret_file_name>\n\n");
        exit(0);
    }
    else
    {
        // Encode mode: validate inputs and hide the secret in the image.
        if (check_operation_type(argv) == e_encode)
        {
            EncodeInfo encInfo;
            if (read_and_validate_encode_args(argv, &encInfo) == e_success)
            {
                do_encoding(&encInfo);
            }
            else
            {
                printf("Error: Invalid arguments for encoding\n");
                exit(0);
            }
        }
        // Decode mode: read the hidden metadata and recover the secret file.
        else if (check_operation_type(argv) == e_decode)
        {
            DecodeInfo decInfo;
            if (read_and_validate_decode_args(argv, &decInfo) == e_success)
            {
                do_decoding(&decInfo);
            }
            else
            {
                printf("Error: Invalid arguments for decoding\n");
                exit(0);
            }
        }
        else
        {
            printf("\nError: Invalid operation\n");
            printf("Please use this Commands :\n");
            printf("For Encoding -> ./a.out -e <src_image.bmp> <secret_file.ext> <stego_image.bmp>\n");
            printf("For Decoding -> ./a.out -d <stego_image.bmp> <secret_file_name>\n\n");
            exit(0);
        }
    }
}
