#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(void){
 	int i, fd, k, k1, data1[10], data2[10];
 	fd=open("data3", O_RDWR|O_CREAT, 0600);
 	for (i=0;i<10;i++){
 		scanf("%d", &data1[i]);
 	}
 	
	// data1 배열의 0-4번째 정수를 “data3" 파일의 0, 2, 4, 6, 8번째 위치에 저장
	for(i=0;i<5;i++){
		write(fd, &data1[i], sizeof(int));
                k = lseek(fd, 4, SEEK_CUR);
	       // printf("[%d]\n", k);
	}


	// data1 배열의 5-9번째 정수를 “data3" 파일의 1, 3, 5, 7, 9번째 위치에 저장
        k = lseek(fd, -36, SEEK_CUR);
        //printf("[%d]\n", k);

	for(i=5;i<10;i++){
                write(fd, &data1[i], sizeof(int));
                k =  lseek(fd, 4, SEEK_CUR);
                //printf("[%d]\n", k);
        }

    	// "data3" 파일에 저장된 정수 10개를 읽어 data2 배열에 저장
     	k = lseek(fd, -44, SEEK_CUR);
	//printf("[%d]\n", k);

	read(fd, data2, sizeof(int)*10);

	
	for (i=0;i<10;i++){
      		printf("%-5d", data1[i]);
       	}
        printf("\n");
        for (i=0;i<10;i++){
         	 printf("%-5d", data2[i]);
        }
        printf("\n");
        return 0;
 }
