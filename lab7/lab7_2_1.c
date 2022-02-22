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
int main(void) {
	int i, status;
	pid_t pid;
	for (i = 0; i < 3; i++) {
		pid = fork();
		if (i==0 && pid ==0) {
			execl("./test1", "test1", "abc", "0");
			exit(0);
		}
		else if (i==1 && pid==0) {
			execl("./test2", "test2", "0");	
			exit(0);
		}
		else if (i==2 && pid==0) {
			execl("./test3", "test3", "0");	
			exit(0);
		}
	}
	for (i = 0; i < 3; i++) {
		wait(&status);	
		if(WIFEXITED(status)){
			printf(".....%d\n", WEXITSTATUS(status));
		}
	}
	exit(0);
}