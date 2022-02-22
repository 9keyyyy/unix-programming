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

  key2=ftok("key", 2);
   // 공유메모리 생성 및 초기화
   for (i=0; i<10; i++){
    // semaphore wait
    // 공유메모리 내용 출력
    }
    shmctl(shmid, IPC_RMID, 0);
     exit(0);
     }