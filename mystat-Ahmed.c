#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>

// Function to print the permissions of a file
void print_permissions(struct stat sb) {
  // Print type of file and permissions
  printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
  printf((sb.st_mode & S_IRUSR) ? "r" : "-");
  printf((sb.st_mode & S_IWUSR) ? "w" : "-");
  printf((sb.st_mode & S_IXUSR) ? "x" : "-");
  printf((sb.st_mode & S_IRGRP) ? "r" : "-");
  printf((sb.st_mode & S_IWGRP) ? "w" : "-");
  printf((sb.st_mode & S_IXGRP) ? "x" : "-");
  printf((sb.st_mode & S_IROTH) ? "r" : "-");
  printf((sb.st_mode & S_IWOTH) ? "w" : "-");
  printf((sb.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");
}

// Function to print details of a file
void print_file_details(const char *filepath) {
  struct stat sb;

  if (stat(filepath, &sb) < 0) {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  // Print out file information
  printf("File Information of %s:\n", filepath);
  printf("File Size: %lld bytes\n", (long long)sb.st_size);
  printf("Number of Blocks Allocated: %lld\n", (long long)sb.st_blocks);
  printf("Number of Links: %ld\n", sb.st_nlink);
  
  // Print permissions of file
  print_permissions(sb);
  
  printf("File Inode: %lu\n", sb.st_ino);
}

int main(int argc, char **argv) {
  // Check for correct command line arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    return 1;
  }
  // Print details of the provided file
  print_file_details(argv[1]);

  return 0;
}
