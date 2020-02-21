#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>

#define BUFFERSIZE 1024

struct sembuf mysem_open = {0, -1, SEM_UNDO};
struct sembuf mysem_close = {0, 1, SEM_UNDO};

union snum
{
	int val;
};

static int semid;

int main( void)
{
	FILE* fp;
	char buffer[BUFFERSIZE];
	union snum s_union;

	semid = semget(2345, 1, 0666);

	// 세마포어 : open
	semop(semid, &mysem_open, 1);

	// 파일 생성 : event.txt
	fp = fopen("event.txt", "w");

	scanf("%s",&buffer);
	fprintf(fp, "%s", buffer);

	// 파일 닫기
	fclose(fp);

	// 세마포어 : close
	semop(semid, &mysem_close, 1);

	exit(0);
}

