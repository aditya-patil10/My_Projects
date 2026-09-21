#ifndef DECODE_H
#define DECODE_H

#include "types.h"

typedef struct _DecodeInfo
{
    // Path to the stego image.
    char *stego_file;
    FILE *fptr_stego_image;

    // Size of the embedded magic string.
    int size_magic_string;
    char magic_string[100];

    // Size of the file extension.
    int size_of_extension;
    char secret_fname[100];

    FILE *output_file;
    int data_size;

}DecodeInfo;

Status do_decoding(DecodeInfo *decInfo);

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

Status open_files_for_decoding(DecodeInfo *decInfo);

Status skip_header_file(DecodeInfo *decodeinfo);

Status skip_header_file(DecodeInfo *decodeinfo);

Status decode_size_magic_string(DecodeInfo *decodeinfo);

int decode_int_from_lsb_image(char *arr);

char decode_string_from_lsb_image(char *arr);

Status decode_magic_string(DecodeInfo *decInfo);

Status decode_secret_file_ext_size(DecodeInfo *decInfo);

Status decode_secret_file_ext(DecodeInfo *decInfo);

Status decode_secret_file_size(DecodeInfo *decInfo);

Status decode_secret_file_data(DecodeInfo *decInfo);


#endif