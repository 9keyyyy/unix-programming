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
void catchint(int);
int main(void){
 	int i, j, num[10], sum=0;
 	static struct sigaction act;
	sigset_t mask;
	act.sa_handler=catchint;
	sigaction(SIGINT, &act, NULL);

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	for (i=0; i<5; i++){
		sigprocmask(SIG_SETMASK, &mask, NULL);
		scanf("%d", &num[i]);
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		sum+=num[i];
		for (j=0; j<=i; j++){
			printf("... %d\n", num[j]);
			sleep(1);
		}		
		printf("SUM=%d\n", sum);
	}
 	exit(0);
}
void catchint(int signo) {
	printf("DO NOT INTERRUPT .... \n");
}
