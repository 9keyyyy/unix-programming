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
void cd_m(char **res){
 //cd 명령 수행
	chdir(res[1]);	
}
void mkdir_m(char **res){
 // mkdir 명령 수행
	mkdir(res[1], 0700);
}
void ls_m(char **res){
 // ls 명령 수행
  	DIR *dp;
	struct dirent *d;
	
	dp = opendir(".");
	d = readdir(dp);
	while(d!=NULL){
		printf("%s\n", d->d_name);
		d=readdir(dp);
	}
	
}
int main(void){ 
  	char name[100], in[50], *res[20]={0};
   	int i;
    	while (1){
     		gets(in);
     		i=0;
      		res[i]=strtok(in, " ");
      		while (res[i]){
      			i++;
      			res[i]=strtok(NULL, " ");
      		}
       		if (!strcmp(res[0], "cd")){
        		cd_m(res);
        	}
         	else if (!strcmp(res[0], "mkdir")){
          		mkdir_m(res);
          	}
           	else if (!strcmp(res[0], "ls")){
            		ls_m(res);
            	}
             	else
              		exit(0);
     	}
}
