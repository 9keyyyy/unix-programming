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
void catchusr(int signo) {
}
int main(void){
 //필요한 변수선언
 	int fd, pid, len=0, n, i;
// signal 처리 설정
	char *addr, *p, buf[512];
	int *addr1;		
	static struct sigaction act;
	act.sa_handler=catchusr;
	sigaction(SIGUSR1, &act, NULL);
 	fd=open("data1", O_RDWR|O_CREAT,0600);
 // memory mapping -> 맵핑된 공간의 크기는 sizeof(구조체)
 	addr = mmap(NULL, 512, PROT_READ, MAP_SHARED, fd, 0);
	addr1 = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
 // 파일크기 조정-> 파일크기 sizeof(구조체)
 	ftruncate(fd, 512);
 // mapping된 공간에 B의 process id 저장(구조체라면 A->pid = getpid();)
	*addr1 = getpid();
	printf("B의 pid=%d\n",*addr1);
  // signal 대기
  	pause();
 	while(strcmp(addr+len, "quit")){
  		printf("reads ... %s\n", addr+len);
		n = 0;
		p = addr+len;
		while(*p!='\0'){
			p++;
			n++;
		}
		len += n;
// len+=(strlen(n)+1)->널문자까지 파일에 저장
		pause(); 
  	}
// 널문자는 안보이므로 출력하면 단어들만 쭉 출력됨
  	for (i=0; i<len; i++)
  		printf("%c",*(addr+i));
  	printf("\n");
  	unlink("data1");
  	printf("bye...\n");
  	exit(0);
  }
