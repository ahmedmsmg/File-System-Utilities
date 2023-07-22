#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH_LENGTH 1024

// Function to print the names of files in the current directory
void list_files(char* dir_path, int long_listing) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[MAX_PATH_LENGTH];

    if (!(dir = opendir(dir_path))) { // Open the directory
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir))) { // Read each entry in the directory
        snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", dir_path, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (long_listing) {
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld", file_stat.st_nlink);

            struct passwd *pwd;
            if ((pwd = getpwuid(file_stat.st_uid)) != NULL)
                printf(" %s", pwd->pw_name); // Print the name of the entry
            else
                printf(" %d", file_stat.st_uid);

            struct group *grp;
            if ((grp = getgrgid(file_stat.st_gid)) != NULL)
                printf(" %s", grp->gr_name);
            else
                printf(" %d", file_stat.st_gid);

            printf(" %5ld", file_stat.st_size);

            char *time_str = ctime(&file_stat.st_mtime);
            time_str[strlen(time_str)-1] = '\0';  // Remove newline character from end
            printf(" %s", time_str);

            printf(" %s\n", entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);  // Close the directory
}

int main(int argc, char **argv) {
    char *dir_path = ".";
    int long_listing = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            long_listing = 1;
        } else {
            dir_path = argv[i];
        }
    }

    list_files(dir_path, long_listing); // Print the names of files in the current directory
    return 0;
}
