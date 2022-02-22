#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    char ch = 'K';
    char* pch = &ch;
    int fd, i;

    fd = open("test1", O_WRONLY|O_TRUNC);
    for (i = 0; i < 3; i++) {
        write(fd, pch, sizeof(char));
    }

    return 0;
}
