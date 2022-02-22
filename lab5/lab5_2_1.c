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
// 출력시 . 부터 출력됨!!! 즉 현재 위치부터 출력되는것
int list(const char *name, const struct stat *status, int type) {
	int cnt=0;
	struct dirent *d;
 	DIR *dp;
	
	
	if(type == FTW_D){
		dp = opendir(name);
	        while(d = readdir(dp)){
			//if(d->d_name[0] != '.') cnt++;
			cnt++;
		}
		if(cnt == 2) printf("%s\n", name);

	}
	return 0;
}
int main(void) {
 	// ftw 호출
 	ftw(".", list, 1);
	return 0;
}
