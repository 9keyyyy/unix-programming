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
void do_child(int id, int p[3][2]){
 	int i, in, pid=getpid();
	for(i=0;i<3;i++){
		close(p[i][1]);
		if(id!=i) close(p[i][0]);
	}
	//close(p[id][1]);
 	while(1){
		read(p[id][0], &in, sizeof(in));
		 if (in==-1)
			 exit(0);
		 else
			 printf("%d %d\n", pid, in);
 	}	
}
int main(void){
 	int i, in, pid, p[3][2];
 
	for(i=0;i<3;i++) pipe(p[i]);

 	for (i=0; i<3; i++){
		 if (fork()==0){
 			do_child(i, p);
 		}
 	}

 	for(i=0;i<3;i++) close(p[i][0]);

 	for(i=0; i<12; i++){
 		scanf("%d", &in);
 		write(p[i%3][1],&in,sizeof(in));
 	}

 	in=-1;
 	for(i=0;i<3;i++)
		write(p[i][1], &in, sizeof(in));

 	for(i=0;i<3;i++)
 		wait(0);

 	exit(0);
}






