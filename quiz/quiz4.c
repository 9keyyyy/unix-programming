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
void catch(int signo){}
void do_child(void){
	int i, in, fd;
	//sigset_t mask;
	//sigemptyset(&mask);
        //sigaddset(&mask, SIGINT);

	fd = open("data1", O_WRONLY|O_CREAT, 0666);
	kill(getppid(), SIGUSR1);
	for (i=0; i<5; i++){
		//sigprocmask(SIG_SETMASK, &mask, NULL);
		scanf("%d", &in);
		write(fd, &in, sizeof(int));	

		printf("child writes %d\n", in);
		kill(getppid(), SIGUSR1);

	}

	exit(0);
}

int main(void){
	int i, in, fd, status, n;
	pid_t pid;
	static struct sigaction act;

	act.sa_handler=catch;
	sigaction(SIGUSR1, &act, NULL);	
	
	if ((pid=fork())==0){
		do_child();
	}
	pause();
	fd = open("data1", O_RDONLY);
	if(fd==-1)printf("error");
	for(i=0; i<5; i++){
		pause();
		//n = lseek(fd, 0, SEEK_CUR);
		//printf("[%d]", n);
		sleep(1);
		read(fd, &in, sizeof(int));                
		printf("parent reads %d\n", in);
	}

	wait(&status);	
	exit(0);
}
