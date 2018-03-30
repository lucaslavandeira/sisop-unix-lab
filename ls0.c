#include <dirent.h>
#include <unistd.h>

void ls0() {
    DIR* dir = opendir(".");

    struct dirent *dirent = readdir(dir);
    while(dirent) {

        // homemade strlen
        size_t bytes = 0;
        char c = dirent->d_name[bytes];
        while (c) {
            bytes++;
            c = dirent->d_name[bytes];
        }

        write(1, dirent->d_name, bytes);
        write(1, "\n", 1);
        dirent = readdir(dir);
    }
    closedir(dir);
}

int main() {
    ls0();
}