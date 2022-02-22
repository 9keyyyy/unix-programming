#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
	
	int fd, i;
	char ch = 'X', ch1 = 'Y', ch2 = 'Z', ch3 = 'T', ch4 = 'S', ch5 = 'W';
	
	fd = open("data1", O_RDWR | O_CREAT, 0600);
	for (i = 0; i < 10; i++) {
		write(fd, &ch, sizeof(char));
	}
	lseek(fd, 0, SEEK_SET);
	write(fd, &ch1, sizeof(char));
	lseek(fd, 0, SEEK_END);
	write(fd, &ch1, sizeof(char));
	
	lseek(fd, 0, SEEK_SET);
	for (i = 0; i < 4; i++) {
		lseek(fd, 1, SEEK_CUR);
		write(fd, &ch2, sizeof(char));
	}

	lseek(fd, 14, SEEK_SET);
	write(fd, &ch3, sizeof(char));
	lseek(fd, -2, SEEK_END);
	write(fd, &ch4, sizeof(char));
	lseek(fd, -2, SEEK_CUR);
	write(fd, &ch5, sizeof(char));
	return 0;
}
