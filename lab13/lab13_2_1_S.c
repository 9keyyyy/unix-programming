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
 char f[6][3]={"f1", "f2", "f3", "f4", "f5", "f6"}; // 6개의 fifo 이름 정의
 char buf[512];
 int i, fd[6], n;
fd_set set, master;
struct timeval t;
 for (i=0;i<6;i++){
 // 6개의 fifo 만들고, open
	mkfifo(f[i], 0600);
	// RDWR? 중요! 이유?!??
	// 한 id의 클라이언트가 여러번 실행을 할 수도 있음
	// readonly를사용하게되면 한번 끝나면 read=0이 되는것을 보고 clear 작업해줘야함
	// 그렇지 않으면 select의 return값이 계속 양수로 생김
	fd[i] = open(f[i], O_RDWR);
 }
  // select 문을 위한 master값 설정
 FD_ZERO(&master);  
 for(i=0;i<3;i++){
	FD_SET(fd[i], &master);
 }
 // select 문의 timer 값 설정
 t.tv_sec = 30;
   while (set=master, select(fd[2]+1, &set, NULL, NULL, &t)>0){
   	for (i=0; i<3; i++){
   		if (FD_ISSET(fd[i], &set)){
   			if (n = read(fd[i], buf, 512)>0){
   				printf("MSG from %d=%s\n", i, buf);
   				n=strlen(buf);
   				// 문자열의 길이 보내기
   				write(fd[i+3], &n, sizeof(int));
   			}
		//	if(n==0){ RDWR이면 필요하지 않음!!
		//		FD_CLR(fd[i], &master);
		//	}
   		}
		t.tv_sec=30;
   	}
   // select 문의 timer 값 재설정
   }
   exit(0);
  }




