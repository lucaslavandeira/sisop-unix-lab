#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256


void tee0(const char* file) {
    int fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd < 0) {
        return 1;
    }

    ssize_t bytes = 0;
    do {
        char buf[BUF_SIZE] = {0};
        bytes = read(0, buf, BUF_SIZE);
        write(1, buf, BUF_SIZE);
        write(fd, buf, BUF_SIZE);
    } while (bytes);

    close(fd);
}

int main(int argc, char** argv) {
    teeo(argv[1]);
}

