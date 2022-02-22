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
#define MSGSIZE 6
void parent(int[][2]);
int child(int, int[][2]);
int main(void){
	int pip[4][2];
	int i, a, b;
	for(i=0;i<4;i++) pipe(pip[i]);
	for (i=0; i<2; i++) {
		if(fork()==0)
			child(i, pip);
	}
	//close(pip[0][0]);
        //close(pip[1][0]);
        //close(pip[2][1]);
        //close(pip[3][1]);

	scanf("%d %d", &a, &b);
	write(pip[0][1], &a, sizeof(int));
	write(pip[1][1], &b, sizeof(int));
	
	read(pip[2][0], &a, sizeof(int));
	read(pip[3][0], &b, sizeof(int));

	printf("parent : %d\n", a);
	printf("parent : %d\n", b);

	for (i=0; i<2; i++) {
		wait(0);
	}
	exit(0);
}

int child(int idx, int p[][2]){
	int pid, i, num, num1, num2;
	int pip[2][2];
	//close(p[0]);
	
	read(p[idx][0], &num, sizeof(int));
	for(i=0;i<2;i++) pipe(pip[i]);

	pid = fork();
	if(pid==0){
		read(pip[0][0], &num1, sizeof(int));
		printf("child-child : %d\n", num1);
		write(pip[1][1], &num1, sizeof(int));	
		exit(0);
	}

	write(pip[0][1], &num, sizeof(int));
	read(pip[1][0], &num2, sizeof(int));
	printf("child : %d\n", num2);
	write(p[idx+2][1], &num2, sizeof(int));

	wait(0);
	exit(0);
}



