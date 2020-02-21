#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>

char strMessgae[20];
int count = 0;
static int semid;

struct sembuf mysem_open = {0,-1, SEM_UNDO};
struct sembuf mysem_close = {0,1, SEM_UNDO};

union snum
{
	int val;
};

void* SaveFile();


int main()
{
	union snum s_union;
	pthread_t pt;
	int thr_id;
	int status;
	int i;

	semid = semget(2345, 1, IPC_CREAT|0666);
	
	s_union.val = 1;

	if(semctl(semid, 0, SETVAL, s_union)== -1) 			return 1;

	thr_id = pthread_create(&pt,NULL,SaveFile,(void*)&i);
	pthread_join(pt, NULL);

	if(semctl(semid, 0, IPC_RMID, s_union)==-1)
	{
		perror("semctl()-IPC_RMID fail\n");
	
	}

	return	0;
}

void* SaveFile()
{
  	FILE *fp;

	printf("내용을 입력하세요.\n");
	printf("==> ");
	semop(semid, &mysem_open, 1);
	scanf("%s\n", strMessgae); 

	fp = fopen("event.txt", "wb");
	
	fwrite(&strMessgae, sizeof(strMessgae), 1, fp);

	fclose(fp);
	semop(semid, &mysem_close,1);
	printf("텍스트저장완료\n");
	
	exit(0);
}
