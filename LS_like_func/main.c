#include "ls_func.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("path: %s\n", argv[1]);
    myls(argv[1]);
    exit(EXIT_SUCCESS);

}
