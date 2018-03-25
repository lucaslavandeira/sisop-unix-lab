#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 4096

void cp0(const char* src, const char* dst) {
    int src_fd = open(src, O_RDONLY);
    int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    char buf[BUF_SIZE] = {0};
    ssize_t bytes = read(src_fd, buf, BUF_SIZE);
    while(bytes) {
        write(dst_fd, buf, bytes);
        bytes = read(src_fd, buf, BUF_SIZE);
    }

    close(src_fd);
    close(dst_fd);
}

int main(int argc, const char** argv) {
    cp0(argv[1], argv[2]);
}
