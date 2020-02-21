#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h> 

#define FILE_NAME "event"
static int semid;

union snum
{
	int val;
};

struct sembuf mysem_open = {0, -1, SEM_UNDO};
struct sembuf mysem_close = {0, 1, SEM_UNDO};

int main(int argc, char* argv[])  
{ 
	FILE *fp;
	char user_input[256];
	union snum s_union;

	semid = semget(2345, 1, IPC_CREAT|IPC_EXCL|0666);

	if(semid == -1)	{
		perror("semget error (alloc)");		
		semid = semget(2345, 1, IPC_CREAT|0666);
	}

	s_union.val = 1; // 세마포어 카운터
	if(semctl(semid, 0, SETVAL, s_union) == -1){
		return 1;
	}

	// sem op
	semop(semid, &mysem_open, 1);

	fp = fopen(FILE_NAME, "wt");
	printf("Please input any character[s](max : 256) :\n"); 
	printf("(Ctl + D : to exit)\n"); 
	while (scanf("%s", user_input) == 1) {
		fprintf(fp, "%s\n", user_input);
	}

	fclose(fp);

	// sem close
	semop(semid, &mysem_close, 1);

    if (semctl(semid, 0, IPC_RMID, s_union) == -1) {
        printf( "semctl()-IPC_RMID Fail\n");
        return -1;
    }

	exit(0);
}