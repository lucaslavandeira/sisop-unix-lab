#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <stdio.h>

void touch1(const char* file) {
    if (utime(file, NULL) < 0) {
        int fd = open(file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fd < 0) {
            perror("Error abriendo el archivo de entrada");
        }

        if (close(fd) < 0) {
            perror("Error cerrando el archivo de entrada");
        }
    };

}

int main(int argc, const char** argv) {
    touch1(argv[1]);
}
