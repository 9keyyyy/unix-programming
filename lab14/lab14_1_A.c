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
 	ushort buf[2]={1, 0};
 	int i, j, pid, semid;
 	key_t key;
 	union semun arg;
 	struct sembuf p_buf;
	key=ftok("key", 3);
	//printf("key: %d\n", key);
	semid=semget(key, 2, 0600|IPC_CREAT|IPC_EXCL);
	if (semid==-1){
 	// semaphore get
	//	printf("1");
 		semid = semget(key, 2, 0);
  	}
  	else{
   	// semaphore 값 초기화
	//	printf("2");
		arg.array=buf;
		semctl(semid, 0, SETALL, arg);   
		semctl(semid, 0, GETALL, arg);
        //printf("%d %d\n", arg.array[0], arg.array[1]);

	}
    	pid=getpid();
     	for (i=0; i<3; i++){
      	// 동기화를 위한 semaphore 연산
		p_buf.sem_num=0;
		p_buf.sem_op=-1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);

	//semctl(semid, 0, GETALL, arg);
        //printf("%d %d\n", arg.array[0], arg.array[1]);
       

      		for (j=0; j<3; j++){
       			printf("%d ... %ld\n", i, pid);
        		sleep(1);
        	}
         // 동기화를 위한 semaphore 연산
		p_buf.sem_num=1;
		p_buf.sem_op=1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);
		//p_buf.sem_num=0;
                //p_buf.sem_op=-1;
                //p_buf.sem_flg=0;
                //semop(semid, &p_buf, 2);
	//semctl(semid, 0, GETALL, arg);
        //printf("%d %d\n", arg.array[0], arg.array[1]);

        }
	semctl(semid, 0, IPC_RMID, 0);
        return 0;
}



