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
void do_child(int num){
	int i, pid;
	static struct sigaction act;
	//void handler(int);
	act.sa_handler=handler;
	sigaction(SIGUSR1, &act, NULL);

	printf("%d-th child is created...\n", num);
	pause();
	// handler함수 만들었고, 함수는 인자로 int하나 받고, return은 없고 void(OS에 리턴)
	// pause() : 시그널이 올때까지 잠들어있는 함수 -> 시그널을 받으면 깨어남
	// 시그널을 받으면 깨어나 handler함수 실행하고 다시 pause 다음문장부터 실행
	// 아래의 함수는 handler안에다가 적어도 됨	

	for(i=0;i<3;i++){
		printf("%ld\n", getpid());
	}
	
	exit(num);
}
int main(void) {
 	int i, cid, status;
 	pid_t pid[3];
 	for (i=0;i<3;i++){
 		pid[i]=fork();
 		if (pid[i]==0) {
 			do_child(i);
 		}
 	}
	for (i=0;i<3;i++){
		sleep(1);
		kill(pid[i], SIGUSR1);
	}
	for (i=0;i<3;i++){
		cid=wait(&status);
		printf("child id=%d, exit status=%d\n", cid, WEXITSTATUS(status));
	}
	exit(0);
}
