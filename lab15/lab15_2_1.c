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
void do_child(int fd) {
 int in;
 pid_t pid=getpid();
 struct flock lock;

 
// record locking
 lock.l_whence=SEEK_SET;
 lock.l_len=sizeof(int);
 lock.l_type=F_WRLCK;
 lock.l_start = 0;
 fcntl(fd, F_SETLKW, &lock);
 lseek(fd, 0, SEEK_SET);
 read(fd, &in, sizeof(int));
 //in = in + 10;
   // 정수 읽기

    printf("%ld reads %d ... \n", pid, in);
     sleep(5);
      in=in+10;
       // 정수 다시 쓰기
	lseek(fd, -sizeof(int), SEEK_CUR);
	write(fd, &in, sizeof(int));  
      printf("%ld writes %d ... \n", pid, in);
         // record unlocking
         lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
          exit(0);
          }
 int main(void){
          int i, in, fd;
          pid_t pid;
          fd=open("data1", O_RDWR|O_CREAT, 0600);
          scanf("%d", &in);
          write(fd, &in, sizeof(int));
	//lseek(fd, -sizeof(int), SEEK_CUR);
	//read(fd, &in, sizeof(int));
//printf("[%d]", in);
          for (i=0; i<3; i++){
              pid=fork();
              if (pid==0)
                   do_child(fd);
          }
          for (i=0; i<3; i++)
                   wait(0);
            // 정수 읽기
	lseek(fd, -sizeof(int), SEEK_CUR);
	read(fd, &in, sizeof(int));
            printf("%d\n", in);
              exit(0);
}
