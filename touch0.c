

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


void touch0(const char* file) {
    int fd = open(file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    close(fd);
}

int main(int argc, char** argv) {
    touch0(argv[1]);
}
