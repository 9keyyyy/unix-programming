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
	int fd, i;
	int *addr;

	fd = open("temp", O_RDONLY|O_CREAT, 0600); // r, w중에 누가 먼저 실행할지 모르므로 creat 붙혀야
	// 어떠한 속도로 입력하냐에 따라 출력되는 결과가 달라짐
	// 즉, 타이밍을 맞추는게 쉽지 않음 (r가 입력되기 전에 출력하면 0이 출력됨)
	addr = mmap(NULL, 20, PROT_READ, MAP_SHARED, fd, 0);
	sleep(5);
	for(i=0;i<5;i++){
		printf("%d\n", *(addr+i));
	}
	sleep(5);
	for(i=5;i<10;i++){
		printf("%d\n", *(addr+i));
	}
	exit(0);
}



