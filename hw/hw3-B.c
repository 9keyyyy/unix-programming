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
int main(){
	static struct sigaction act;
	act.sa_handler = catch;
	sigaction(SIGUSR1, &act, NULL);

	int fd, pid, n, num;
	fd = open("data1", O_RDWR);
	pid = getpid();
	write(fd, &pid, sizeof(int));
 	while(1){
		pause();
		n = read(fd, &num, sizeof(int));
		if(n>0) {
			printf("reads... %d\n", num);
		}
		else {
			//sleep(1);
			break;
		}
	}
	printf("bye...\n");
	return 0;	
}
