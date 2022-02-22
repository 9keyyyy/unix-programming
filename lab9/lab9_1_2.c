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
void handler(int signo){
}
void do_child(int i, int *cid){
	int j, pid;
	pid=getpid();
	static struct sigaction act;
	act.sa_handler=handler;
	sigaction(SIGUSR1, &act, NULL);
	
	if(i!=4) pause();	
	
	for (j=0;j<5;j++){
	printf("child %d .... \n", pid);
	sleep(1);
	}
	if(i!=0) kill(cid[i-1], SIGUSR1);

	exit(0);
}
int main(void) {
	int i, status;
	pid_t pid[5];
	for (i=0;i<5;i++){
		pid[i]=fork();
		if (pid[i]==0) {
			do_child(i, pid);
		}	
	}
	for (i=0;i<5;i++){
		wait(&status);
	}
	exit(0);
}

