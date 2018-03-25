#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

void touch1(const char* filename) {
    if (utime(filename, NULL) < 0) {
        int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        close(fd);
    };

}

int main(int argc, const char** argv) {
    touch1(argv[1]);
}
