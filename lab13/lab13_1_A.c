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
int main(void){
 	char f[2][3]={"f1", "f2"};
 	int i, in, fd[2];
 	// FIFO 2개 만들기
	mkfifo(f[0], 0600);
	mkfifo(f[1], 0600); 
	// “f1”과 “f2” open
	// A와 B에서 모두 rdonly를 먼저하게되면 블락킹(상대편도 준비될때까지 기다리므로)-> deadlock
	// 순서 중요! fifo 순서대로!
	fd[0] = open(f[0], O_WRONLY);
	fd[1] = open(f[1], O_RDONLY);

   	for (;;){
     		scanf("%d", &in);
      		// “f1”으로 정수 보내기
		write(fd[0], &in, sizeof(int));
       		if (in==-1)
        		exit(0);
         	// “f2”에서 정수 읽기
		read(fd[1], &in, sizeof(int)); 
         	printf("%d\n", in);
           }
           return 0;
 }




