#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>

// Function to recursively search through the directory tree
void recursive_search(char *basePath) {
    char path[PATH_MAX];
    struct dirent *dp;
    DIR *dir = opendir(basePath); // Open the directory

    if (!dir) {
        perror("opendir");
        return;
    }

    printf("Current Path %s\n", basePath); // Print the current path

    while ((dp = readdir(dir)) != NULL) { // Read each entry in the directory
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) { 
            printf("%s\n", dp->d_name); // Print the name of the entry

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (dp->d_type == DT_DIR) { // If the entry is a directory, recursively search through it
                recursive_search(path);
            }
        }
    }

    closedir(dir); // Close the directory
}

int main(int argc, char *argv[]) {
    char cwd[PATH_MAX];

    if (argc > 2) { // If a directory is provided as an argument, search through it
        printf("No more than 2 arguments\n");
        return 1;
    }

    if (argc == 2) {
        recursive_search(argv[1]);
    } else { // Otherwise, search through the current working directory
        getcwd(cwd, sizeof(cwd));
        recursive_search(cwd);
    }

    printf("Search has finished!\n");

    return 0;
}

