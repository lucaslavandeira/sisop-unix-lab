#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_SIZE 4096

void cp0(const char* src, const char* dst) {
    int src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("Error abriendo archivo de entrada");
        return;
    }

    int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (dst_fd < 0) {
        perror("Error creando archivo destino");
        return;
    }

    ssize_t bytes = 0;
    do {
        char buf[BUF_SIZE] = {0};
        bytes = read(src_fd, buf, BUF_SIZE);

        if (bytes < 0) {
            perror("Error leyendo del archivo de entrada");
            return;
        }

        if (write(dst_fd, buf, (size_t) bytes) < 0) {
            perror("Error escribiendo al archivo destino");
            return;
        }

    } while(bytes);

    if (close(src_fd) < 0) {
        perror("Error cerrando el archivo de entrada");
        return;
    }

    if (close(dst_fd) < 0) {
        perror("Error cerrando el archivo destino");
        return;
    }
}

int main(int argc, const char** argv) {
    cp0(argv[1], argv[2]);
}
