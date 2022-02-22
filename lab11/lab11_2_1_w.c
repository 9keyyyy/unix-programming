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
int main(void){
	int fd,fd1, i, len=0, n, pid;
	char *addr;
	static struct sigaction act;
	act.sa_handler = catch;
	sigaction(SIGUSR1, &act, NULL);
	
	fd = open("temp", O_RDONLY|O_CREAT, 0600);
	fd1 = open("data", O_RDWR|O_CREAT, 0666);
	pid = getpid();
	write(fd1, &pid, sizeof(int));
	addr = mmap(NULL,512 , PROT_READ, MAP_SHARED, fd, 0);
	for(i=0;i<3;i++){
		pause();
//		sleep(5);
		read(fd1, &n, sizeof(int));		
		write(1, addr+len, 512);
		len += n;
		write(1, "-------\n", 8);
	}	
	exit(0);
}





