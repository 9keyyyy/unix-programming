#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ftw.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
void do_child(int fd) {
	char buf[5] = { 0 };
	
	read(fd, buf, sizeof(char)*2);
	printf("%c %c, pid = %ld\n", buf[0], buf[1], getpid());
	exit(0); 
}
int main(int argc, char ** argv) {
	int num, i, fd;
	pid_t pid;
	num = atoi(argv[2]);
	fd = open(argv[1], O_RDONLY);
	for (i = 0; i < num; i++) {
		pid = fork();
		if (pid==0) {
			do_child(fd);
		}
	}
	for (i = 0; i < num; i++) {
		wait(0);
	}
	return 0;
}
