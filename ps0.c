#define _BSD_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


void ps0() {
    const char* proc = "/proc";
    DIR* proc_root = opendir(proc);
    if (!proc_root) {
        perror("Error opening proc dir");
    }

    struct dirent* ent = readdir(proc_root);
    while (ent) {
        if (ent->d_type != DT_DIR) {
            ent = readdir(proc_root);
            continue;
        }

        char comm[17] = {0};
        snprintf(comm, 17, "/proc/%s/comm", ent->d_name);

        int fd = open(comm, O_RDONLY);
        if (fd < 0) {
            if (errno != ENOENT) {
                perror("Error opening process comm file");
                return;
            }
            ent = readdir(proc_root);
            continue; // not a pid
        }
        char proc_name[256] = {0};
        read(fd, proc_name, 256);

        printf("%s %s", ent->d_name, proc_name);
        ent = readdir(proc_root);
    }
}

int main(int argc, char *argv[]) {
    ps0();
}
