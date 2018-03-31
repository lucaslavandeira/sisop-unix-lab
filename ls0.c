#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void ls0() {
    DIR* dir = opendir(".");

    if (!dir) {
        perror("Error abriendo el directorio");
        return;
    }

    errno = 0;
    struct dirent *dirent = readdir(dir);
    while(dirent) {

        // homemade strlen
        size_t bytes = 0;
        char c = dirent->d_name[bytes];
        while (c) {
            bytes++;
            c = dirent->d_name[bytes];
        }

        if (write(STDOUT_FILENO, dirent->d_name, bytes) < 0) {
            perror("Error escribiendo el nombre de archivo");
            return;
        }
        write(1, "\n", 1);
        dirent = readdir(dir);
    }

    if (errno) {
        perror("Error leyendo el directorio");
        return;
    }

    if (closedir(dir) < 0) {
        perror("Error cerrando el directorio");
        return;
    }
}

int main() {
    ls0();
}