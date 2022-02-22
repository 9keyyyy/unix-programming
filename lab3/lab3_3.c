#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(void){

	struct stat buf;
	
	// buf에 “data3” 파일의 속성을 저장
 	stat("data3", &buf);
	// mode, link수, 크기 출력
	printf("%o %d %ld\n", buf.st_mode & 0777, buf.st_nlink, buf.st_size);
 	
	return 0;
}
