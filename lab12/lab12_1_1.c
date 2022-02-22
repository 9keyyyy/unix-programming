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
void do_child(int id, int p[2][2]){
 	char buf='a';
 	int i, pid=getpid();

	if(id!=2) read(p[id][0], &buf, sizeof(char));
 	for(i=0; i<5; i++){
 		sleep(1);
 		printf("%ld\n", pid);
 	}
 	if(id!=0)write(p[id-1][1], &buf, sizeof(char));
 	exit(0);
}
int main(void){
 	int i, in, pid, p[2][2];
	pipe(p[0]);
	pipe(p[1]);
 	for (i=0; i<3; i++){
 		if (fork()==0){
 			do_child(i, p);
 		}	
 	}
 	for(i=0;i<3;i++)
 		wait(0);
 	exit(0);
}




