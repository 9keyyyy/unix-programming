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
void cat_m(char** res) {
	char buf[512]; // buffer 크기는 512 bytes 입니다. 이 부분은 수정하지 마세요.
	int fd, n;
	fd = open(res[1], O_RDONLY);
	if(fd == -1) return;
	while(1){
		n = read(fd, buf, sizeof(buf));
		if(n==0) break;
		write(1, buf, n);
	}
}
void cd_m(char** res) {
	chdir(res[1]);
}
void cp_m(char** res) {
	char buf[512]; // buffer 크기는 512 bytes 입니다. 이 부분은 수정하지 마세요.
	int fd1, fd2, n;
	fd1 = open(res[1], O_RDONLY);
	if(fd1==-1) return;
	fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
	while(1){
		n = read(fd1, buf, sizeof(buf));
		if(n==0) break;
		write(fd2, buf, n);
	}	
}
void mkdir_m(char** res) {
	mkdir(res[1], 0700);	
}
void ls_m(char** res) {
	DIR *dp;
	struct dirent *d;
	struct stat buf;

	dp = opendir(".");
	d = readdir(dp);

	while(d!=NULL){
		if(d->d_name[0] == '.'){
			d = readdir(dp);
			continue;
		}
		stat(d->d_name, &buf);
		if(S_ISREG(buf.st_mode)){
			printf("F\t%o\t%d\t%d\t%d\t%ld\t%s\t%s\n", buf.st_mode & 0777, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size, strtok(ctime(&buf.st_mtime), "\n"), d->d_name);
		}
		else if (S_ISDIR(buf.st_mode)){
			printf("D\t%o\t%d\t%d\t%d\t%ld\t%s\t%s\n", buf.st_mode & 0777, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size, strtok(ctime(&buf.st_mtime), "\n"), d->d_name);
		}
		
		d = readdir(dp);
	}		
}
int main(void) { // main 함수는 수정하지 말고, 사용하세요.
	char in[50], * res[20] = { 0 }, buf[100] = {0};
	char* inst[5] = { "cat", "cd", "cp", "mkdir", "ls" };
	void (*f[5])(char**) = { cat_m, cd_m, cp_m, mkdir_m, ls_m };
	int i;
	while (1) {
		// current working directory 이름 출력		
		getcwd(buf, 99);
		printf("%s> ", buf);
		
		gets(in);
		if (in[0] == '\0')
			continue;
		i = 0;
		res[i] = strtok(in, " ");
		while (res[i]) {
			i++;
			res[i] = strtok(NULL, " ");
		}
		if (strcmp(res[0], "exit") == 0)
			exit(0);
		for (i = 0; i < 5; i++) {
			if (!strcmp(res[0], inst[i])) {
				f[i](res);
				break;
			}
		}
	}
}
// rewinddir(DIR *dirptr); 로 디렉토리 파일 포인터 위치 제일 처음으로 이동 가능
