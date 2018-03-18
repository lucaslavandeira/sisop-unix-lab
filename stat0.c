#include <sys/stat.h>
#include <unistd.h>

#define DEC_START 48  // ASCII 48 = '0'
#define FSIZE_DIGITS_MAX 16  // ext4 max 16tb ~ 16 digits string buffer

long math_pow(int base, int exp) {
    long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

size_t long_to_str(long n, char* buf, size_t size) {
    long partial_sum = 0;
    long divisor;
    unsigned int decimal_pos = 1;
    do {
        divisor = math_pow(10, decimal_pos++);
        long remainder = (n % divisor - partial_sum) / (divisor / 10);
        partial_sum += remainder * (divisor / 10);
        buf[size - decimal_pos] = (char) (DEC_START + remainder);
    } while(divisor <= n);

    if (decimal_pos < size) {  // Borrado de 'leading zeroes'
        for (int i = 0; i < decimal_pos; i++) {
            buf[i] = buf[i + size - decimal_pos];
        }
    }
    return decimal_pos - 1;
}

int main(int argc, char** argv) {
    struct stat buf;
    stat(argv[1], &buf);
    char int_str[FSIZE_DIGITS_MAX] = {0};
    size_t digits = long_to_str(buf.st_size, int_str, FSIZE_DIGITS_MAX);
    write(1, "Size: ", 6);
    write(1, int_str, digits);
    write(1, "\n", 1);

    write(1, "File: ", 6);
    size_t strlen = 0;
    char i = -1;
    while(i != '\0') {
        i = argv[1][strlen++];
    }
    write(1, argv[1], strlen - 1);
    write(1, "\n", 1);

    write(1, "Type: ", 6);
    if ((buf.st_mode & S_IFMT) == S_IFREG) {
        write(1, "regular file\n", 13);
    } else if ((buf.st_mode & S_IFMT) == S_IFDIR) {
        write(1, "directory\n", 10);
    }
    return 0;
}
