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
// 필요한 변수선언
 	int fd, len = 0, pid, n;
// addr 구조체를 선언해 사용하는 것!!!
	char *addr, buf[512];
	fd=open("data1", O_RDWR);
 	if (fd==-1){
 		printf("Reader Not Ready....\n");
 		return 0;
 	}
 	addr=mmap(NULL, 512, PROT_PROT_WRITE, MAP_SHARED, fd, 0);

	// A->pid==0이면 계속 반복
	// !!! shared 메모리 공간은 모두 0으로 초기화시켜 나에게 줌!!!
 	while(read(fd, &pid, sizeof(int))==0){
 		sleep(3);
 	}
 	printf("B의 pid=%d\n", pid);
        // 남아있는 공간은 (처음 선언한 구조체 크기-1)
	n=read(0, addr+len, 512);
	*(addr+len+n-1)='\0';

	while(strcmp(addr+len, "quit")){
 		printf("writes ..... %s\n", addr+len);
		kill(pid, SIGUSR1);
		len += n-1;	
 		n=read(0, addr+len, 512);
		*(addr+len+n-1) = '\0';
 	}
	 // B에게 signal 보내기
 	kill(pid, SIGUSR1);
	printf("bye...\n");
 	exit(0);
 }
