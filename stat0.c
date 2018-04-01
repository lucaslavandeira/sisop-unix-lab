#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void stat0(const char* file) {
    struct stat s;
    if (stat(file, &s) < 0) {
        perror("Error en stat del archivo de entrada");
        return;
    }

    static const char *msg =
            "Size: %d\n"
            "File: %s\n"
            "Type: %s\n";

    const char *type;
    if (S_ISREG(s.st_mode)) {
        type = "regular file";
    } else if (S_ISDIR(s.st_mode)) {
        type = "directory";
    } else {
        return;
    }
    printf(msg, s.st_size, file, type);
}

int main(int argc, char** argv) {
    stat0(argv[1]);
    return 0;
}
