#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
	int in = 35;
	int* pin = &in;
	int fd, i;

	fd = open("test2", O_WRONLY|O_CREAT, 0640);
	for (i = 0; i < 10; i++) {
		write(fd, pin, sizeof(int));
	}
	
	return 0;
}
