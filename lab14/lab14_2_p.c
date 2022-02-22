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
struct addr {
	char str[10][512];
//	int front[10];
	int rear[10];
//	int index[10];
};
union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};
int main(){
	int fd, i, semid, *addr, n;
	key_t key;
	union semun arg;
	struct sembuf p_buf;
	ushort buf[3] = {0, 1, 10};
	struct addr *A;
	char tmp[512];

	key=ftok("key", 1);
	semid = semget(key, 3, 0600|IPC_CREAT|IPC_EXCL);
	if(semid==-1){
		semid = semget(key, 3, 0);
	}	
	else{
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}
	fd = open("data", O_RDWR|O_CREAT, 0600);
	A = mmap(NULL, 512, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	ftruncate(fd, sizeof(A));
	i = 0;
	while(1){
		// semwait(e);
		p_buf.sem_num=2;
		p_buf.sem_op=-1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);
		
		// semwait(s);
		p_buf.sem_num=1;
		p_buf.sem_op=-1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);

		n = read(0, tmp, 512);
		tmp[n-1] = '\0';
		printf("[%s]\n", tmp);
		if(strcmp(tmp, "quit")) break;
		strcpy(A->str[i], tmp);
		printf("!");
		//if(i==0) {
			//A->front[i] = 0;
			A->rear[i] = n + 1;
		//}
		//else  {
			//A->front[i] = rear[i-1]+1;
			//A->rear[i] = rear[i-1]+ n + 2;
		//}
		write(1, A->str[i], n+1);
		write(1, &A->rear[i], sizeof(int));
		
		// semsignal(s);
		p_buf.sem_num=1;
		p_buf.sem_op=1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);
		
		// semsignal(n);		
		p_buf.sem_num=0;
		p_buf.sem_op=1;
		p_buf.sem_flg=0;
		semop(semid, &p_buf, 1);
		
		i++;
		i = i%10;
	}	
	semctl(semid, 0, IPC_RMID, 0);
	return 0;

}
