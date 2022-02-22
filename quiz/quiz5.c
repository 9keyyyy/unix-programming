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
void do_child(int p[5][2]){
        char buf='a';
        int i,n, flag, pid=getpid(), id;
//	fd_set set, master;
//	FD_ZERO(&master);
//
//	for(i=0;i<5;i++)
//		FD_SET(p[i][0], &master);
//
//	while(set=master, select(p[4][0]+1, &set, NULL, NULL, NULL)>0){
//		flag = 0;
//		for(i=0;i<5;i++){
//			if(FD_ISSET(p[i][0], &set)){
//				if(n=read(p[i][0], &id, 4)>0){
//					flag = 1;
//					break;
//				}
//			}
//		}
//		if(flag==1) break;
//	}

	read(p[0][0], &id, sizeof(int));
	printf("pid=%d, id=%d\n", pid, id);
	
       	if(id>1) read(p[id-1][0], &buf, sizeof(char));

        for(i=0; i<5; i++){
//                sleep(1);
                printf("%ld\n", pid);
		sleep(1);
        }

        if(id<5) write(p[id][1], &buf, sizeof(char));
        exit(0);
}
int main(void){
        int i, in, pid, p[5][2];
        for(i=0; i<5; i++)
                pipe(p[i]);

	for (i=0; i<5; i++){
		scanf("%d", &in);
		write(p[0][1], &in, sizeof(int));		
	}

        for (i=0; i<5; i++){
                if (fork()==0){
                        do_child(p);
                }
        }

        for(i=0; i<5; i++)
                wait(0);

        exit(0);
}
