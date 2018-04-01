#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

void ln0(const char* from, const char* to) {
    if (symlink(from, to) < -1) {
        perror("Error creando el symlink");
        return;
    }
}

int main(int argc, const char** argv) {
    ln0(argv[1], argv[2]);
}
