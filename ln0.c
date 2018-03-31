#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>


/*
 * Pregunta: ¿Qué ocurre si se intenta crear un enlace a un archivo que no existe?
 * Se crea un symlink roto: el fs va a seguir el enlance pero va a ir a parar
 * a un archivo no existente. Por ejemplo, hacer un cat de un symlink
 * roto va a devolver el error de archivo inexistente
 */

void ln0(const char* from, const char* to) {
    if (symlink(from, to) < -1) {
        perror("Error creando el symlink");
        return;
    }
}

int main(int argc, const char** argv) {
    ln0(argv[1], argv[2]);
}
