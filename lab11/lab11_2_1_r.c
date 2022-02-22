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
	int fd, m, fd1, i, len=0, n, pid;
	char *addr;

	fd = open("temp", O_RDWR|O_CREAT, 0666);
	fd1 = open("data", O_RDWR|O_CREAT, 0666);
	while(m == 0) m =read(fd1, &pid, sizeof(int));

	addr = mmap(NULL, 512, PROT_WRITE, MAP_SHARED, fd, 0);
	
	ftruncate(fd, 512);
	for(i=0;i<3;i++){
		n = read(0, addr+len, 512);
		len += n;
		write(fd1, &n, sizeof(int));
		kill(pid, SIGUSR1);
	}
	exit(0);	
}




