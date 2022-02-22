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
int main(int argc, char** argv) {
	int i, j, num;
	num = argc;
	for (i = 0; i < 3; i++) {
		for (j = 1; j<num; j++) {
			printf("%s", argv[j]);
		}
		printf("\n");
	}
	exit(0);
}
