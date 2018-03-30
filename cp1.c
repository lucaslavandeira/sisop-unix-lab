#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void cp1(const char* src, const char* dst) {

    size_t page_size = (size_t) sysconf(_SC_PAGESIZE);
    int fd = open(src, O_RDWR);

    if (fd < 0) {
        perror("Error opening src");
        return;
    }

    int o_fd = open(dst, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (o_fd < 0) {
        perror("Error opening dst");
        return;
    }

    size_t offset = 0;
    struct stat s;
    if (fstat(fd, &s) < 0) {
        perror("Error getting stat of fd");
        return;
    }

    size_t remaining = s.st_size - offset;
    size_t bytes_to_write =  page_size;
    while (remaining) {
        if (remaining < page_size) {
            bytes_to_write = remaining;
        }

        void *map_src = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
        if (map_src == MAP_FAILED) {
            perror("Error mapping src");
            return;
        }

        if (ftruncate(o_fd, offset + bytes_to_write)) {
            perror("Error seeking to end of o_fd");
            return;
        }

        void *mmap_dst = mmap(NULL, bytes_to_write, PROT_READ | PROT_WRITE, MAP_SHARED, o_fd, offset);
        if (mmap_dst == MAP_FAILED) {
            perror("Error mapping dst");
            return;
        }

        memcpy(mmap_dst, map_src, bytes_to_write);
        munmap(mmap_dst, bytes_to_write);
        munmap(map_src, bytes_to_write);
        offset += bytes_to_write;
        remaining -= bytes_to_write;
    }

    close(fd);
    close(o_fd);
}

int main(int argc, char** argv) {
    cp1(argv[1], argv[2]);
    return 0;
}

