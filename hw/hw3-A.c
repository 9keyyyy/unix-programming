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
int main(){
	int fd, m = 0, pid, n;

	
	fd = open("data1", O_RDWR|O_CREAT, 0666);
	while(m == 0) m = read(fd, &pid, sizeof(int));
	//printf("pid = %d\n", pid);
	
	while(1){
		scanf("%d", &n);
		if(n>=0) {
			printf("writes ..... %d\n", n);
			write(fd, &n, sizeof(int));
		}
		sleep(1);
		kill(pid, SIGUSR1);
		if(n<0) break;
	}
	printf("bye...\n");
	return 0;
}
