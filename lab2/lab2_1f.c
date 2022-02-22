#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int data[10]={0};
    int fd, i;

    fd = open("test2", O_RDONLY);
    read(fd, data, sizeof(int)*5);
    for (i = 0; i < 5; i++) {
        printf("%d\n", data[i]);
    }

    return 0;
}