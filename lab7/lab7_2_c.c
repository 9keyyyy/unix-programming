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
int main(int argc, char** argv){
	
	int i, fd;
	char c;
	fd = open("data", O_RDONLY);
	for(i=0;i<10;i++){
		read(fd, &c, 1); 
		printf("%c\n", c);
		sleep(1);
	}
	exit(2);	
}
