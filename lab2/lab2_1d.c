#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    char ch = 'Z';
    char* pch = &ch;
    int fd, i;

    fd = open("test1", O_WRONLY|O_APPEND);
    for (i = 0; i < 5; i++) {
        write(fd, pch, sizeof(char));
    }

    return 0;
}
