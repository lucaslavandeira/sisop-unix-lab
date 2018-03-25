#include <unistd.h>
#include <stdio.h>


void rm1(const char* file) {
    if (unlink(file)) {
        char msg[256];
        snprintf(msg, 256, "rm: cannot remove %s", file);
        perror(msg);
    }
}

int main(int argc, char** argv) {
    rm1(argv[1]);
}

