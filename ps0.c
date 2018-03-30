#define _BSD_SOURCE 
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>


#define PROC_PATH_BUF_SIZE 17  // /path/<pid>/stat es a lo sumo 17 bytes
#define PROC_NAME_BUF_SIZE 256

#define STAT_CONTENT_BUF_SIZE 1024

void ps0() {
    const char* proc = "/proc";
    DIR* proc_root = opendir(proc);
    if (!proc_root) {
        perror("Error opening proc dir");
        return;
    }

    struct dirent* ent = readdir(proc_root);
    while (ent && !errno) {
        if (ent->d_type != DT_DIR) {
            ent = readdir(proc_root);
            continue;
        }

        int is_pid = 1;
        int i = 0;
        char cur = ent->d_name[i++];
        while (cur) {
            if (!isdigit(cur)) {
                is_pid = 0;
                break;
            }
            cur = ent->d_name[i++];
        }

        if (!is_pid) {
            ent = readdir(proc_root);
            continue;
        }

        char comm[PROC_PATH_BUF_SIZE] = {0};
        snprintf(comm, PROC_PATH_BUF_SIZE, "/proc/%s/comm", ent->d_name);

        int comm_fd = open(comm, O_RDONLY);
        if (comm_fd < 0) {
            perror("Error opening process comm file");
            return;
        }

        char proc_name[PROC_NAME_BUF_SIZE] = {0};
        read(comm_fd, proc_name, PROC_NAME_BUF_SIZE);

        char stat[PROC_PATH_BUF_SIZE] = {0};
        snprintf(stat, PROC_PATH_BUF_SIZE, "/proc/%s/stat", ent->d_name);

        int stat_fd = open(stat, O_RDONLY);
        if (stat_fd < 0) {
            perror("Error opening process stat file");
            close(comm_fd);
            return;
        }

        char stat_content[STAT_CONTENT_BUF_SIZE] = {0};
        read(stat_fd, stat_content, STAT_CONTENT_BUF_SIZE);
        char status;
        int matched = sscanf(stat_content, "%*s %*s %c", &status);

        if (matched != 1) {
            printf("Error running sscanf on stat file\n");
            close(comm_fd);
            close(stat_fd);
            return;
        }

        printf("%5s %c %s", ent->d_name, status, proc_name);
        ent = readdir(proc_root);

        close(comm_fd);
        close(stat_fd);
    }

    if (errno) {
        perror("Error reading /proc dirent");
    }
}

int main(int argc, char *argv[]) {
    ps0();
}
