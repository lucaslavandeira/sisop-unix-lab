#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_SIZE 256


void tee0(const char* file) {
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd < 0) {
        return;
    }

    ssize_t bytes = 0;
    do {
        char buf[BUF_SIZE] = {0};
        bytes = read(STDIN_FILENO, buf, BUF_SIZE);

        if (bytes < 0) {
            perror("Error leyendo de entrada estándar");
            return;
        }

        if (write(STDOUT_FILENO, buf, bytes) < 0) {
            perror("Error escribiendo a salida estándar");
            return;
        }

        if (write(fd, buf, bytes) < 0) {
            perror("Error escribiendo al archivo de salida");
            return;
        }

    } while (bytes);

    if (close(fd) < 0) {
        perror("Error cerrando el archivo de salida");
    }
}

int main(int argc, char** argv) {
    tee0(argv[1]);
}

