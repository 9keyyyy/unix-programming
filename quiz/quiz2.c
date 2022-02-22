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
void rm_m(char **res){
	char buf[501];
	int cnt;
        struct stat s;
        struct dirent *d1, *d2;
        DIR *dp1, *dp2;

        dp1=opendir(res[1]);
	chdir(res[1]);               
	d1 = readdir(dp1);
	while(d1!=NULL){
		stat(d1->d_name, &s);
		//printf("stat %s\n", d1->d_name);
		if(d1->d_name[0] == '.'){
			d1 = readdir(dp1);
			continue;
		}

		if(S_ISREG(s.st_mode)){
			//printf("file\n");
			remove(d1->d_name);
		}
		else if(S_ISDIR(s.st_mode)){
			//printf("D %s\n", d1->d_name);
			cnt = 0;
			dp2 = opendir(d1->d_name);
			//chdir(d1->name);
			d2 = readdir(dp2);
			
			while(d2!=NULL){	
				if(d2->d_name[0] == '.'){
                        d2 = readdir(dp2);
                        continue;
                }

				cnt++;
				d2 = readdir(dp2);
			}
			//printf("cnt %d\n", cnt);
			if(cnt==0) rmdir(d1->d_name);
			else{
				printf("%s has %d files or directories\n", d1->d_name, cnt);
			}
		}
		//else{printf("else\n");}
		d1 = readdir(dp1);
	}

    


	chdir("..");                   
	if (rmdir(res[1])==-1)
		printf("cannot remove %s\n", res[1]);
}

int main(void){              
        char name[100], in[50], *res[20]={0};
        int i;

        while (1){
		getcwd(name, 99);
               	printf("%s> ", name);
        	gets(in);
		i=0;
        	res[i]=strtok(in, " ");
		while (res[i]){
			i++;
			res[i]=strtok(NULL, " ");
		}

        	if (!strcmp(res[0], "rm")){
        			rm_m(res);
		}
        	else
        		exit(0);
	}
}
