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

int main(){
	char ch[100], ch1[100];
	struct stat buf;

	scanf("%s", ch);
	lstat(ch, &buf);
        printf("%s %o %ld\n", ch, buf.st_mode&0777, buf.st_size);

	readlink(ch, ch1, buf.st_size);	
	stat(ch, &buf);
	printf("%s %o %ld\n", ch1, buf.st_mode&0777, buf.st_size);

}
