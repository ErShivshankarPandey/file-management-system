#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_CREATE 1
#define ID_DELETE 2
#define ID_UPDATE 3
#define ID_READ 4
#define ID_OVERWRITE 5
#define ID_EXIT 6
#define ID_CLEAR 7

HWND hOutputBox, hFilenameBox, hContentBox;
HFONT hFont;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void AddControls(HWND hwnd);
void AppendToOutputBox(const char *text);
void PerformFileOperation(int operation);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"FileManagerGUI";
    wc.lpfnWndProc = WindowProcedure;
    wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"FileManagerGUI", L"File Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 1000, 850, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            AddControls(hwnd);
            break;
        case WM_COMMAND:
            switch (wp) {
                case ID_CREATE:
                case ID_DELETE:
                case ID_UPDATE:
                case ID_READ:
                case ID_OVERWRITE:
                    PerformFileOperation(wp);
                    break;
                case ID_CLEAR:
                    SetWindowText(hOutputBox, "");
                    break;
                case ID_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

void AddControls(HWND hwnd) {
    hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                       TEXT("Segoe UI"));

    CreateWindow("STATIC", "Filename:", WS_VISIBLE | WS_CHILD,
                 30, 30, 100, 30, hwnd, NULL, NULL, NULL);
    hFilenameBox = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                140, 30, 800, 30, hwnd, NULL, NULL, NULL);
    SendMessage(hFilenameBox, WM_SETFONT, (WPARAM)hFont, TRUE);

    CreateWindow("STATIC", "Content:", WS_VISIBLE | WS_CHILD,
                 30, 70, 100, 30, hwnd, NULL, NULL, NULL);
    hContentBox = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL,
                               140, 70, 800, 200, hwnd, NULL, NULL, NULL);
    SendMessage(hContentBox, WM_SETFONT, (WPARAM)hFont, TRUE);

    CreateWindow("BUTTON", "Create File", WS_VISIBLE | WS_CHILD,
                 30, 300, 150, 40, hwnd, (HMENU)ID_CREATE, NULL, NULL);
    CreateWindow("BUTTON", "Delete File", WS_VISIBLE | WS_CHILD,
                 190, 300, 150, 40, hwnd, (HMENU)ID_DELETE, NULL, NULL);
    CreateWindow("BUTTON", "Update File", WS_VISIBLE | WS_CHILD,
                 350, 300, 150, 40, hwnd, (HMENU)ID_UPDATE, NULL, NULL);
    CreateWindow("BUTTON", "Read File", WS_VISIBLE | WS_CHILD,
                 510, 300, 150, 40, hwnd, (HMENU)ID_READ, NULL, NULL);
    CreateWindow("BUTTON", "Overwrite File", WS_VISIBLE | WS_CHILD,
                 670, 300, 150, 40, hwnd, (HMENU)ID_OVERWRITE, NULL, NULL);
    CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD,
                 830, 300, 100, 40, hwnd, (HMENU)ID_EXIT, NULL, NULL);
    CreateWindow("BUTTON", "Clear Output", WS_VISIBLE | WS_CHILD,
                 830, 750, 150, 30, hwnd, (HMENU)ID_CLEAR, NULL, NULL);

    hOutputBox = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL,
                              30, 360, 910, 370, hwnd, NULL, NULL, NULL);
    SendMessage(hOutputBox, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void AppendToOutputBox(const char *text) {
    int length = GetWindowTextLength(hOutputBox);
    SendMessage(hOutputBox, EM_SETSEL, length, length);
    SendMessage(hOutputBox, EM_REPLACESEL, 0, (LPARAM)text);
}

void PerformFileOperation(int operation) {
    char filename[260];
    char content[2048];

    GetWindowText(hFilenameBox, filename, sizeof(filename));
    GetWindowText(hContentBox, content, sizeof(content));

    if (strlen(filename) == 0) {
        MessageBox(NULL, "Please enter a filename!", "Warning", MB_ICONWARNING);
        return;
    }

    FILE *file;

    switch (operation) {
        case ID_CREATE:
            file = fopen(filename, "w");
            if (file) {
                fprintf(file, "%s", content);
                fclose(file);
                AppendToOutputBox("File created successfully.\r\n");
            } else {
                char msg[300];
                sprintf(msg, "Failed to create file: %s", filename);
                MessageBox(NULL, msg, "Error", MB_ICONERROR);
            }
            break;
        case ID_DELETE:
            if (remove(filename) == 0) {
                AppendToOutputBox("File deleted successfully.\r\n");
            } else {
                char msg[300];
                sprintf(msg, "Failed to delete file: %s", filename);
                MessageBox(NULL, msg, "Error", MB_ICONERROR);
            }
            break;
        case ID_UPDATE:
            file = fopen(filename, "a");
            if (file) {
                fprintf(file, "%s", content);
                fclose(file);
                AppendToOutputBox("File updated successfully.\r\n");
            } else {
                char msg[300];
                sprintf(msg, "Failed to update file: %s", filename);
                MessageBox(NULL, msg, "Error", MB_ICONERROR);
            }
            break;
        case ID_OVERWRITE:
            file = fopen(filename, "w");
            if (file) {
                fprintf(file, "%s", content);
                fclose(file);
                AppendToOutputBox("File overwritten successfully.\r\n");
            } else {
                char msg[300];
                sprintf(msg, "Failed to overwrite file: %s", filename);
                MessageBox(NULL, msg, "Error", MB_ICONERROR);
            }
            break;
        case ID_READ:
            file = fopen(filename, "r");
            if (file) {
                char buffer[1024];
                AppendToOutputBox("File contents:\r\n");
                while (fgets(buffer, sizeof(buffer), file)) {
                    AppendToOutputBox(buffer);
                }
                AppendToOutputBox("\r\n\r\n");
                fclose(file);
            } else {
                char msg[300];
                sprintf(msg, "Failed to read file: %s", filename);
                MessageBox(NULL, msg, "Error", MB_ICONERROR);
            }
            break;
    }
}

