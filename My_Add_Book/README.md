# 📒 Address Book Management System

A **menu-driven Address Book Management System developed in C** that allows users to efficiently store, manage, search, update, and delete contact information.

The project demonstrates core C programming concepts such as **structures, arrays, functions, pointers, strings, and file handling**.

## 🚀 Features

- ➕ Add new contacts
- 🔍 Search for contacts
- ✏️ Edit existing contacts
- 🗑️ Delete contacts
- 📋 Display all contacts
- 💾 Save contacts to a file
- 📂 Load contacts from a file
- 📌 Supports up to 100 contacts
- 🖥️ Simple menu-driven interface

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC
- **Concepts Used:**
  - Structures
  - Arrays
  - Functions
  - Pointers
  - Strings
  - File Handling
  - Conditional Statements
  - Loops

## 📂 Project Structure

```text
Address-Book/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── contacts.txt
└── README.md
```

> The exact file names may vary depending on the implementation.

## ⚙️ How to Compile

Clone the repository:

```bash
git clone <your-repository-link>
cd Address-Book
```

Compile the project using GCC:

```bash
gcc *.c -o addressbook
```

Run the program:

```bash
./addressbook
```

On Windows:

```bash
addressbook.exe
```

## 🖥️ Program Menu

The application provides a menu similar to:

```text
===== ADDRESS BOOK =====

1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. Display Contacts
6. Save Contacts
7. Exit

Enter your choice:
```

## 📞 Contact Information

Each contact can contain information such as:

- Name
- Phone Number
- Email Address

The information is stored using a **structure**, making it easier to manage multiple contacts.

## 💾 File Handling

The project uses **file handling in C** to store contact information permanently.

This allows the contacts to be:

- Saved to a file
- Loaded when the program starts
- Updated when changes are made

Therefore, contacts are not lost when the application is closed.

## 🧠 Concepts Learned

This project helped in understanding and implementing:

- Structure-based data management
- Passing structures to functions
- Arrays of structures
- String manipulation
- Searching and modifying data
- File opening, reading, writing, and closing
- Menu-driven programming
- Modular programming using multiple `.c` and `.h` files

## 🎯 Purpose of the Project

The main purpose of this project is to build a practical C application while strengthening fundamental programming concepts and understanding how real-world data can be managed using **structures and file handling**.

## 👨‍💻 Author

**Aditya S. Patil**

---

⭐ If you found this project useful, feel free to star the repository!
