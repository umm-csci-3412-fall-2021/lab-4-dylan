#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs = 0, num_regular = 0;

bool is_dir(const char* path) {
  struct stat buf;

  // If the error code of stat is 0 then everything went fine, then reutnr the check of the File Type (st_mode)
  if(stat(path, &buf)==0) {
    return S_ISDIR(buf.st_mode);
  }
  
  // Not a dir if the above check fails
  return false;
}

void process_path(const char*);

void process_directory(const char* path) {
  DIR *dir = opendir(path);
  struct dirent *cur;

  // Change to our working directory
  chdir(path);
  
  // Loop through everything in the current directory
  while((cur = readdir(dir)) != NULL){
    // Check if d_name is "." or ".." as that signifies we're at the end of that tree 'branch'
    if(strcmp(".",cur->d_name) != 0 && strcmp("..",cur->d_name) != 0){
      process_path(cur->d_name);
    }
  }

  // Increment our directory counter, move back, and make sure to close the aforementioned directory
  num_dirs++;
  chdir("..");
  closedir(dir);
}

void process_file(const char* path) {
  num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
