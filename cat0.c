#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_SIZE 256

void cat0(const char* file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        return;
    }

    ssize_t bytes = 0;
    do {
        char buf[BUF_SIZE] = {0};
        bytes = read(fd, buf, BUF_SIZE);

        if (bytes < 0) {
            perror("Error leyendo del archivo de entrada");
            return;
        }

        if (write(STDOUT_FILENO, buf, BUF_SIZE) < 0) {
            perror("Error escribiendo a salida estándar");
            return;
        }

    } while (bytes == BUF_SIZE);

    close(fd);
}

int main(int argc, char** argv) {
    cat0(argv[1]);
    return 0;
}
