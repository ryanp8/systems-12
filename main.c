#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {

    DIR *d;
    d = opendir(".");

    struct dirent *entry = readdir(d);
    struct stat sb;
    unsigned long long size = 0;

    while(entry) {
        stat(entry->d_name, &sb);
        size += sb.st_size;
        entry = readdir(d);
    }
    printf("Statistics for directory: .\n");
    printf("Total Directory Size: %llu Bytes\n", size);

    rewinddir(d);
    entry = readdir(d);

    printf("Directories:\n");
    while (entry) {
        if (entry->d_type == 4) {
            stat(entry->d_name, &sb);
            size += sb.st_size;
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    rewinddir(d);
    entry = readdir(d);

    printf("Regular files:\n");
    while (entry) {
        if (entry->d_type == 8) {
            stat(entry->d_name, &sb);
            size += sb.st_size;
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    return 0;
}