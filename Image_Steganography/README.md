# Image Steganography in C

A command-line C application that hides supported secret files inside a BMP image and extracts them when needed.

## Features

- Encode a secret file into a BMP image
- Decode and recover a hidden file from a stego image
- Supports BMP images for encoding
- Command-line interface
- Input validation for encoding and decoding
- Modular implementation with separate encode and decode modules

## Supported Secret File Types

The application can hide the following file types:

- .txt
- .mp3
- .jpeg
- .png
- .mp4

## Project Structure

Image-Steganography/
│
├── main.c          # Entry point and command-line operation handling
├── encode.c         # Encoding logic
├── encode.h         # Encoding function declarations
├── decode.c         # Decoding logic
├── decode.h         # Decoding function declarations
├── types.h          # Structures, enums, and custom data types
└── README.md

## Usage

### Encode a Secret File

```bash
./a.out -e <src_image.bmp> <secret_file.ext> <stego_image.bmp>
```

Example:

./a.out -e beautiful.bmp secret.txt stego.bmp

- `beautiful.bmp` — source BMP image  
- `secret.txt` — secret file to hide  
- `stego.bmp` — output image containing the hidden file  

### Decode a Secret File

./a.out -d <stego_image.bmp> <secret_file_name>


Example:

./a.out -d stego.bmp decoded_secret.txt

- `stego.bmp` — image containing the hidden data  
- `decoded_secret.txt` — recovered secret file  

## Command-Line Options

 Option             Description 
| `-e` | Encode a secret file into a BMP image |
| `-d` | Decode a secret file from a stego BMP image |

## Concepts Used

- C programming
- Structures (`struct`)
- File handling
- Binary file operations
- Bitwise operations
- Arrays and strings
- Pointers
- Command-line arguments
- Error handling
- Modular programming

## Author

Aditya Patil