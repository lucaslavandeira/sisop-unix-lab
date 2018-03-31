#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

/*
 * Pregunta: ¿se puede usar mv0 para renombrar archivos dentro del mismo directorio?
 * Sí, usar mv es la "forma unix" de renombrar archivos
 */

void mv0(const char* oldpath, const char* newpath) {
    if (rename(oldpath, newpath) < 0) {
        perror("Error en rename");
        return;
    }
}

int main(int argc, const char** argv) {
    mv0(argv[1], argv[2]);
}
