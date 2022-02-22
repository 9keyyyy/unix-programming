#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void cat_m(char **res){     	
	char buf[512];
	int fd, n;
	
	fd = open(res[1], O_RDONLY);
	if(fd==-1){

		return;
	}
	while(1){
		n = read(fd, buf, sizeof(buf));
		if(n==0) break;
		write(1, buf, n);
	
	}
	
}

void cp_m(char **res){     	
	char buf[512];
	int fd1, fd2, n;
	fd1 = open(res[1], O_RDONLY);
	if(fd1==-1) return;
	fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC,0600 );
	while(1){
		n = read(fd1, buf, sizeof(buf));
		if(n==0) break;
		write(fd2, buf, n);
	}
	}
	

void vi_m(char **res){     	
	char buf[512];
	int fd, n;

	
}             
int main(void){              	
	char in[50], *res[20]={0};
	char *inst[3]={"cat", "cp", "vi"};
	void (*f[3])(char **)={cat_m, cp_m, vi_m};
	int i;

	while (1){
		printf("> ");
		gets(in);
		if (in[0]=='\0')
			continue;

		i=0;
		res[i]=strtok(in, " ");
		while (res[i]){
			i++;
			res[i]=strtok(NULL, " ");
		}

		if (strcmp(res[0], "exit")==0)
			exit(0);

		for (i=0;i<3;i++){
			if (!strcmp(res[0], inst[i])){
				f[i](res);
				break;
			}
		}
	}
}