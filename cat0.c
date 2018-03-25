#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256

void cat0(const char* file) {
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }

    ssize_t bytes = 0;
    do {
        char buf[BUF_SIZE] = {0};
        bytes = read(fd, buf, BUF_SIZE);
        write(1, buf, BUF_SIZE);
    } while (bytes == BUF_SIZE);

    close(fd);
}

int main(int argc, char** argv) {
    cat0(argv[1]);
    return 0;
}

