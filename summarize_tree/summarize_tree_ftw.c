#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>

#define MAX_FTW_DEPTH 16

static int num_dirs = 0, num_regular = 0;

static int callback(const char *fpath, const struct stat *sb, int typeflag){
    // If the type is 0, it's a file
    if(typeflag == 0){
        num_regular++;
    }
    // Likewise, if a type is 1 or 2, it's a directory
    if(typeflag == 1 || typeflag == 2){
        num_dirs++;
    }

    return 0;
}

int main(int argc, char** argv) {
    ftw(argv[1], callback, MAX_FTW_DEPTH);

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
