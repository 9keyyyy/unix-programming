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
int list(const char *name, const struct stat *status, int type) {
 	if (type==FTW_D || type==FTW_DNR){
 		printf("%s : %d\n", name, status->st_size);
 	}
 	else if (type==FTW_F){
 		if (S_IXUSR & status->st_mode || S_IXGRP & status->st_mode ||S_IXOTH & status->st_mode)
 			printf("%s : %d\n", name, status->st_size);
 	}	
 	return 0;
}
int main(void) {
 // ftw 호출
 	ftw(".", list, 1); 
	return 0;
}
