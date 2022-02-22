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

	fd = open("temp", O_RDWR|O_CREAT, 0666);
	addr = mmap(NULL, 20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, sizeof(int)*5);
	for(i=0;i<10;i++){
		scanf("%d", addr+i);
	}
	exit(0);
}


