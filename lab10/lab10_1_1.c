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
void catchalarm(int);
int main(void){
 int i, num, sum=0, ret;
 static struct sigaction act;
 act.sa_handler = catchalarm;
sigaction(SIGALRM, &act, NULL);
 for (i=0; i<10; i++){
 do{
alarm(10);
ret = scanf("%d", &num);
}while(ret<0);
alarm(0);
 sum+=num;
 printf("sum=%d\n", sum);
 }
 exit(0);
}
void catchalarm(int signo){
 printf("input !!! input !!! input !!!\n");
}

