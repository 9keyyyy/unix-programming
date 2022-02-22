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
union semun{
 int val;
 struct semid_ds *buf;
 ushort *array;
};
int main(void){
int shmid, semid, i, n, *buf;
 key_t key1, key2;
 union semun arg;
 struct sembuf p_buf;
 key1=ftok("key", 1);
// semaphore 생성 및 초기화
semid = semget(key1, 1, 0600|IPC_CREAT|IPC_EXCL);
  key2=ftok("key", 2);
if(semid==-1){
	semid=semget(key1, 1, 0);
}
else{
	arg.val=0;
	semctl(semid, 0, SETVAL, arg);
}
   // 공유메모리 생성 및 초기화
shmid=shmget(key2, 10*sizeof(int), 0600|IPC_CREAT);
buf = (int *)shmat(shmid, 0, 0);
   for (i=0; i<10; i++){
	
    // 공유메모리에 입력
	scanf("%d", buf+i);
     // semaphore signal
     p_buf.sem_num=0;
	p_buf.sem_op=1;
	p_buf.sem_flg=0;
	semop(semid, &p_buf, 1);	
     }
      exit(0);
      }
