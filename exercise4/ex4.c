/* 
 * Copyright ©2023 Amal Jacob
 * Name: Amal Jacob
 * Email: amalj3@uw.edu
 */

#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h>   // for directory ops
#include <unistd.h>   // for read / write

#include "ro_file.h"

#define READBUFSIZE 128

/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);

// Writes contents of a file given a full filepath out to stdout. Exits
// if an error occurs.
void WriteContents(char *filepath);

/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  // Needs to be given a directory name
  if (argc != 2) {
    fprintf(stderr, "Please give directory name as exactly one arg.\n");
    return EXIT_FAILURE;
  }

  DIR *dirp = opendir(argv[1]);
  // Needs to be a valid directory
  if (dirp == NULL) {
    fprintf(stderr, "Please give valid directory name.\n");
    return EXIT_FAILURE;
  }

  struct dirent *file = readdir(dirp);
  while (file != NULL) {
    if (IsTxtFile(file->d_name)) {
      WriteContents(Concatenate(argv[1], file->d_name));
    }
    file = readdir(dirp);
  }

  if (closedir(dirp) == -1) {
    fprintf(stderr, "closedir failed.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


/*** HELPER FUNCTION DEFINITIONS *******************************************/

void WriteContents(char *filepath) {
  RO_FILE* fin;
  char readbuf[READBUFSIZE];
  size_t readlen;

  // Open input file
  fin = ro_open(filepath);
  if (fin == NULL) {
    perror("ro_open for read failed");
    exit(EXIT_FAILURE);
  }

  // Read file's contents and write into stdout
  while ((readlen = ro_read(readbuf, READBUFSIZE, fin)) > 0) {
    if (fwrite(readbuf, 1, readlen, stdout) < readlen) {
      perror("fwrite failed");
      ro_close(fin);
      exit(EXIT_FAILURE);
    }
  }

  // Clean up
  ro_close(fin);
  free(filepath);
}

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}
