#include "../headers.h"

char validFileName(char *file_address) {

    char *ext = strrchr(file_address, '.');

    if (ext == NULL) {
        printw("missing extension\n");
        return 1;
    }

    if (strcmp(ext, ".txt") == 0) {
        return 0;
    }

    printw("invalid file extension\n");
    return 1;
    // create a constant to get the file extension of the file address give
}
