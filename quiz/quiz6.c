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
struct q_entry{
        long mtype;
        int data;
};

void do_child(int qid){
             int i, pid=getpid(), id;
	struct q_entry msg;

	msgrcv(qid, &msg, sizeof(int), 1, 0);
	id = msg.data;
	printf("pid=%d, id=%d\n", pid, id);

        if (id>1){
        	msgrcv(qid, &msg, sizeof(int), id, 0);	      
	}

            for(i=0; i<5; i++){
                sleep(1);
                printf("%ld\n", pid);
            }

        if (id<5){
        	msg.mtype = id+1;
		msgsnd(qid, &msg, sizeof(int), 0);       
	}

            exit(0);   
}

int main(void){
        int i, in, pid, qid;
        key_t key;
        struct q_entry msg;

        key=ftok("key", 2);
 	qid = msgget(key, 0600|IPC_CREAT);       

        for (i=0; i<5; i++){
	      	scanf("%d", &in);
              	msg.mtype = 1;
		msg.data = in;
		msgsnd(qid, &msg, sizeof(int), 0);
       }

        for (i=0; i<5; i++){
                if (fork()==0){
                        do_child(qid);   
                }
        }

        for(i=0; i<5; i++)
                wait(0);
        exit(0);
}
