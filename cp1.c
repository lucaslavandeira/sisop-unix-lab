#define _POSIX_C_SOURCE 200112L
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void cp1(const char* src, const char* dst) {

    size_t page_size = (size_t) sysconf(_SC_PAGESIZE);
    if (page_size == -1 && errno == EINVAL) {
        perror("Error obteniendo el tamaño de página del sistema");
        return;
    }

    int src_fd = open(src, O_RDWR);
    if (src_fd < 0) {
        perror("Error abriendo archivo de entrada");
        return;
    }

    int dst_fd = open(dst, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (dst_fd < 0) {
        perror("Error creando archivo destino");
        return;
    }

    size_t offset = 0;
    struct stat s;
    if (fstat(src_fd, &s) < 0) {
        perror("Error en stat del archivo de entrada");
        return;
    }

    size_t remaining = s.st_size - offset;
    size_t bytes_to_write =  page_size;
    while (remaining) {
        if (remaining < page_size) {
            bytes_to_write = remaining;
        }

        void *map_src = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, src_fd, offset);
        if (map_src == MAP_FAILED) {
            perror("Error mappeando src");
            return;
        }

        if (ftruncate(dst_fd, offset + bytes_to_write)) {
            perror("Error truncando dst");
            return;
        }

        void *mmap_dst = mmap(NULL, bytes_to_write, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, offset);
        if (mmap_dst == MAP_FAILED) {
            perror("Error mappeando dst");
            return;
        }

        if (!memcpy(mmap_dst, map_src, bytes_to_write)) {
            perror("Error copiando memoria de src a dst");
            return;
        }

        if (munmap(mmap_dst, bytes_to_write) < 0) {
            perror("Error en el unmap de dst");
            return;
        }

        if (munmap(map_src, bytes_to_write) < 0) {
            perror("Error en el unmap de src");
            return;
        }

        offset += bytes_to_write;
        remaining -= bytes_to_write;
    }

    if (close(src_fd) < 0) {
        perror("Error cerrando el archivo de entrada");
        return;
    }

    if (close(dst_fd) < 0) {
        perror("Error cerrando el archivo destino");
        return;
    }
}

int main(int argc, char** argv) {
    cp1(argv[1], argv[2]);
    return 0;
}

