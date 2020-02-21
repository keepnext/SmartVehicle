#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>

int count = 0;

void *myThreadFunc(void *data);

// 작업 세마포어 p 연산 -----
struct sembuf mysem_open = {0,-1, SEM_UNDO};
struct sembuf mysem_close = {0,1, SEM_UNDO};
// 작업 세마포어 v 연산 -----


union snum
{
	int val;
};

static int semid;

int main(int argc, char **argv)
{
	int thr_id;
	int status;
	int i;
	union snum s_union;
	pthread_t pt;

// 작업 세마포어 생성 시작 -----

	
	semid = semget(2345, 1, IPC_CREAT|0666);
	
	s_union.val = 1;

	if(semctl(semid, 0, SETVAL, s_union)== -1) return 1;
	 pthread_create(&pt,NULL,myThreadFunc,(void*)&i);
	if(thr_id<0)
	{
		perror("Thread create Error\n"); 
		return 1;
	}
	
// 작업 세마포어 생성 종료 -----

	pthread_join(pt, NULL);
// 작업 세마포어 해제 시작 -----
    
	if(semctl(semid, 0, IPC_RMID, s_union)==-1)
	{
		perror("semctl()-IPC_RMID fail\n");
	
	}
// 작업 세마포어 해제 종료 -----
}

void *myThreadFunc(void *data){
	int thread_num = *(int *)data;
	int lnum;
	printf("Thread Create %d\n", thread_num);

// 작업 세마포어 사용 시작 -----
	FILE *fp;
	char msg[20]; 
	int nresult = 0;	

	while(nresult != 2)
	{
		semop(semid, &mysem_open, 1);

		if ((fp = fopen("event.txt", "r")) != NULL ) {
			printf("find file!!\n");
			printf("Message : ");
			while (fread(&msg, sizeof(msg), 1, fp) > 0) 
			{
				if (msg != NULL) {
					printf("[ %s ] \n",msg);
					printf("RemoveFile : event.txt \n");
					remove("event.txt");
					exit(0);
				}
			}
			break;					
			nresult = 2;

		}else {
		
			printf("find...\n");

		}
		
		semop(semid, &mysem_close,1);

		sleep(1);
	
	}

// 작업 세마포어 사용 종료 -----
}
