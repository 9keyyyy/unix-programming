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
void do_child(void) {
	printf("process id: %ld, group id: %ld, session id: %ld\n", getpid(), getppid(), getsid(getpid()));
	exit(0); 
}
int main(int argc, char** argv) {
	int num, i;
	pid_t pid;
	
	num = atoi(argv[1]);
	for (i = 0; i < num; i++) {
		pid = fork();
		if (pid==0) {
			do_child();
		}
	}
	for (i = 0; i < num; i++) { 
		wait(0);
	}
	return 0;
}