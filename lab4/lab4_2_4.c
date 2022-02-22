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

int main(){
	mkdir("A",0700);
	mkdir("A/B",0700);
	mkdir("A/B/C",0700);
	symlink("A/B/C", "T");
	// directory permission
	// 4 : 해당 디렉톨 ㅣ아래 있는 파일 내가 볼 수 있는지
	// 2 : 해당 디렉토리 아래 피알이나 서브디렉 생성 가능한지
	// 1 : 해당 디레고리로 cd가 가능한지 
}
