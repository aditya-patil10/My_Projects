# MP3 Tag Reader & Editor

## 📌 Project Overview

**MP3 Tag Reader & Editor** is a command-line-based application developed in **C** for reading and editing metadata stored in MP3 files.

The project works with MP3 **ID3 tags** and allows users to view existing metadata or edit specific information such as **Title, Artist, Album, Year, Genre, and Comments**.

The application uses command-line arguments to perform different operations.

---

## 🚀 Features

- View MP3 metadata
- Edit song Title
- Edit Artist name
- Edit Album name
- Edit Year
- Edit Genre
- Edit Comments
- Validate MP3 file input
- Read and modify binary MP3 tag data
- Command-line based interface
- Supports ID3 tag frame processing
- Uses temporary file handling during editing

---

## 🛠️ Technologies & Concepts Used

- **Programming Language:** C
- File Handling
- Binary File Operations
- Command-Line Arguments
- Structures
- Pointers
- Dynamic Memory Allocation
- String Handling
- Memory Management
- Endianness / Byte Order Conversion
- Modular Programming
- ID3 Tag Processing

---

## 📂 Project Structure

```text
MP3_Tag_Reader/
│
├── main.c          # Handles command-line arguments and program flow
├── view.c          # Reads and displays MP3 tag information
├── edit.c          # Edits MP3 tag information
├── files.h         # Function declarations and shared definitions
└── README.md       # Project documentation
```

---

## ⚙️ Compilation

Compile the project using GCC:

```bash
gcc main.c view.c edit.c -o a.out
```

---

## ▶️ How to Use

### 1. Display Help Menu

```bash
./a.out --help
```

The help menu displays all available operations and their formats.

---

### 2. View MP3 Metadata

To display the metadata of an MP3 file:

```bash
./a.out -v <file_name.mp3>
```

Example:

```bash
./a.out -v song.mp3
```

The program can display information such as:

- Title
- Artist
- Album
- Year
- Genre
- Comments

---

### 3. Edit MP3 Metadata

The edit operation follows this format:

```bash
./a.out -e <tag_option> "<new_value>" <file_name.mp3>
```

### Edit Title

```bash
./a.out -e -t "My Song" song.mp3
```

### Edit Year

```bash
./a.out -e -y "2026" song.mp3
```

### Edit Artist

```bash
./a.out -e -a "Artist Name" song.mp3
```

### Edit Album

```bash
./a.out -e -A "Album Name" song.mp3
```

### Edit Genre

```bash
./a.out -e -g "Rock" song.mp3
```

### Edit Comments

```bash
./a.out -e -c "My Comments" song.mp3
```

---

## 📋 Command Options

| Option | Operation |
|---|---|
| `--help` | Display help menu |
| `-v` | View MP3 metadata |
| `-e` | Edit MP3 metadata |
| `-t` | Edit Title |
| `-y` | Edit Year |
| `-a` | Edit Artist |
| `-A` | Edit Album |
| `-g` | Edit Genre |
| `-c` | Edit Comments |

---

## 🔍 How the Project Works

### View Operation

When the user selects the view option:

```bash
./a.out -v song.mp3
```

the program:

1. Validates the MP3 file.
2. Opens the file in binary read mode.
3. Reads the ID3 header.
4. Reads the metadata frames.
5. Identifies the required tag information.
6. Converts the frame size where required.
7. Displays the metadata to the user.

---

### Edit Operation

When the user selects an edit option:

```bash
./a.out -e -t "New Title" song.mp3
```

the program:

1. Validates the MP3 file.
2. Opens the original MP3 file.
3. Reads the ID3 header and metadata frames.
4. Identifies the frame corresponding to the selected tag.
5. Replaces the existing tag data with the new value.
6. Writes the updated information to a temporary MP3 file.
7. Preserves the remaining MP3 data.
8. Updates the original file with the modified information.

---

## 🧠 Concepts Learned

This project provides practical experience with several important C programming concepts:

- **File Handling** – Opening, reading, writing, and closing files.
- **Binary File Handling** – Processing raw binary data from MP3 files.
- **Pointers** – Passing and manipulating data using pointers.
- **Dynamic Memory Allocation** – Allocating memory for variable-sized tag data.
- **Structures** – Organizing related data.
- **Command-Line Arguments** – Using `argc` and `argv` to control program operations.
- **String Handling** – Comparing and manipulating tag values.
- **Endianness** – Handling byte-order conversion for MP3 frame sizes.
- **Functions** – Dividing the project into reusable modules.
- **Modular Programming** – Separating the project into `main.c`, `view.c`, `edit.c`, and header files.

---

## 🎯 Project Objective

The main objective of this project is to understand how metadata is stored inside an MP3 file and to implement a C program capable of reading and modifying that metadata using **file handling and binary data processing**.

---

## 👨‍💻 Author

**Aditya S. Patil**

---

## 📄 License

This project was developed for educational and learning purposes.