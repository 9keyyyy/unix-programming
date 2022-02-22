#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	char ch = 'K';
	int fd, i;
	
// 읽기용	fd = open("data1", O_RDONLY);
// 쓰기용.파일 이미 있으면 기존파일 오픈&그렇지 않을 경우 새로 오픈
// fd = open("test1", O_WRONLY | O_CREAT, 0644);
// 파일이 없다면 새로 만들어지고, 있다면 기존내용 모두 지워지고 오픈
// fd = open("test1", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 파일 오픈되자마자 포인터가 파일의 제일 뒤
// fd = open("test1", O_WRONLY | O_APPEND);

// 파일이 이미 존재하면 오픈 실패, 없으면 새로 만들어지고 오픈
	fd = open("test1", O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (fd == -1) {
			printf("open error ............\n");
		}
		else {
			for (i = 0; i < 10; i++) {
				write(fd, &ch, sizeof(char));
			}
		}
	return 0;
}
