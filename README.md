# file-management-system

## 📁 File Management System

### 🛠 Description
This is a **Windows GUI-based File Management System** developed in C using the **Win32 API**. It allows users to:

- Create a new file with content
- Delete an existing file
- Update a file by appending content
- Overwrite an existing file
- Read and display file contents
- Clear the output box
- Exit the application

This project provides a user-friendly interface with text input fields and buttons for file operations.

---

### 💡 Features

- ✅ GUI using native Win32 API
- ✅ File Create, Read, Update, Delete, and Overwrite
- ✅ Dark-themed Segoe UI font
- ✅ Output log box to show results and file content
- ✅ Error pop-ups for missing files or invalid actions

---

### 🔧 How to Compile & Run

#### 🧰 Requirements

- Windows OS
- A C compiler that supports Windows API (e.g., MinGW or MSVC)
- **Visual Studio** or **VS Code** with C/C++ extension

#### 🖥️ Using MinGW (Command Line)
gcc Project.c -o Project.exe -mwindows

#### ▶️ Run the program
Project.exe

> Note: `-mwindows` is used to compile GUI-based applications without opening a console window.
