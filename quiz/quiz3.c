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
             char name[100], buf[100], in[50], *res[20]={0};
             int i, status;
	     pid_t pid;

             while (1){
		
		getcwd(buf, 99);
		printf("%s > ", buf);
        	gets(in);
		if (in[0]=='\0')
			continue;

		i=0;
     	        res[i]=strtok(in, " ");
		while (res[i]){
			res[++i]=strtok(NULL, " ");
		}

        	if (strcmp(res[0], "exit")==0){
        		exit(0);
		}
		else{
			pid = fork();
			if(pid==0){
				execv(res[0], res);
				exit(0);
			}
			else{
				wait(0);
			}
			//execv(res[0], res);
			//exit(0);
		}
	   }

        	return 0;
}

