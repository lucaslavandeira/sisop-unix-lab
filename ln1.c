#define _POSIX_C_SOURCE 200809L
#include <unistd.h>


/*
¿Cuál es la diferencia entre un hard link y un soft link?

Crear un hard link a un archivo, luego eliminar el archivo original ¿Qué pasa con el enlace? ¿Se perdieron los datos del archivo?

Repetir lo mismo, pero con un soft link. ¿Qué pasa ahora con el enlace? ¿Se perdieron los datos esta vez?

 */

void ln0(const char* from, const char* to) {
    link(from, to);
}

int main(int argc, const char** argv) {
    ln0(argv[1], argv[2]);
}
