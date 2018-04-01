#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

void mv0(const char* oldpath, const char* newpath) {
    if (rename(oldpath, newpath) < 0) {
        perror("Error en rename");
        return;
    }
}

int main(int argc, const char** argv) {
    mv0(argv[1], argv[2]);
}
