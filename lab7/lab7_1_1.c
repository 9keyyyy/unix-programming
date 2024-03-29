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
void do_child(int num) {
	int i;
	for (i = 0; i < 5; i++) {
		printf("%ld ... %ld ... %ld\n", getpid(), getpgid(0), getsid(getpid()));	
		sleep(1);
	}
	exit(num);
}
int main(void) {
	int i, status;
	pid_t pid;
	for (i = 0; i < 3; i++) {
		pid = fork();
		if (pid==0) {
			do_child(i);
		}
	}
	for (i = 0; i < 3; i++) {
		wait(&status);
		if (WIFEXITED(status)) {	
			printf("......%d\n", WEXITSTATUS(status));
		}
	}
	exit(0);
}
