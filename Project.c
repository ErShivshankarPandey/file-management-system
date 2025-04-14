#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void createFile();
void deleteFile();
void updateFile();
void readFile();
void overwriteFile();

int main() {
    int choice;

    while (1) {
        // Menu Options
        printf("\n===== FILE MANAGEMENT SYSTEM =====\n");
        printf("1. Create a File\n");
        printf("2. Delete a File\n");
        printf("3. Update a File\n");
        printf("4. Read a File\n");
        printf("5. Overwrite a File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: updateFile(); break;
            case 4: readFile(); break;
            case 5: overwriteFile(); break;
            case 6: 
                printf("Exiting File Management System...\n");
                exit(0);
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to Create a File
void createFile() {
    char filename[100];
    FILE *file;

    printf("Enter the name of the file to create: ");
    scanf(" %99[^\n]", filename);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
    } else {
        printf("File '%s' created successfully.\n", filename);
        fclose(file);
    }
}

// Function to Delete a File
void deleteFile() {
    char filename[100];

    printf("Enter the name of the file to delete: ");
    scanf(" %99[^\n]", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error deleting file! It may not exist.\n");
    }
}

// Function to Update a File (Append Content)
void updateFile() {
    char filename[100];
    char content[500];
    FILE *file;

    printf("Enter the name of the file to update: ");
    scanf(" %99[^\n]", filename);
    getchar(); // Consume newline

    file = fopen(filename, "a"); // Open file in append mode
    if (file == NULL) {
        printf("Error opening file! Make sure the file exists.\n");
        return;
    }

    printf("Enter content to append: ");
    fgets(content, sizeof(content), stdin);

    fprintf(file, "%s", content);
    fclose(file);

    printf("Content added to '%s' successfully.\n", filename);
}

// Function to Read a File
void readFile() {
    char filename[100];
    char ch;
    FILE *file;

    printf("Enter the name of the file to read: ");
    scanf(" %99[^\n]", filename);

    file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error opening file! Make sure the file exists.\n");
        return;
    }

    printf("\nContents of the file '%s':\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("\n");
}

// Function to Overwrite a File
void overwriteFile() {
    char filename[100];
    char content[500];
    FILE *file;

    printf("Enter the name of the file to overwrite: ");
    scanf(" %99[^\n]", filename);
    getchar(); // Consume newline

    file = fopen(filename, "w"); // Open file in write mode (overwrite)
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter new content for the file: ");
    fgets(content, sizeof(content), stdin);

    fprintf(file, "%s", content);
    fclose(file);

    printf("File '%s' content overwritten successfully.\n", filename);
}
