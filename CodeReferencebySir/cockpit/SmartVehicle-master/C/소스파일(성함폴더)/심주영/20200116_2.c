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
	int n = 0;
	char buffer[BUFFERSIZE];
	union snum s_union;

	// 세마포어 자원 할당
	semid = semget(2345, 1, IPC_CREAT|IPC_EXCL|0666);
	if(semid == -1)	{
		perror("semget error (alloc)");		
		semid = semget(2345, 1, IPC_CREAT|0666);
	}
	s_union.val = 1; // 세마포어 카운터
	if(semctl(semid, 0, SETVAL, s_union) == -1){
		return 1;
	}

	while (1) {
		// 세마포어 : open
		semop(semid, &mysem_open, 1);

		fp = fopen("event.txt", "r");
		if(fp != NULL) { // 파일이 있는 경우
			// 실행 : 화면에 출력
			printf("실행\n");
			while((n = fread(buffer, sizeof(char) * 2, 1, fp)) > 0) {
				printf("%s", buffer); 
			}
			printf("\n");
			fclose(fp);

			// 실행 : 파일 삭제
			if (fork( ) == 0) {
				execl("/bin/rm", "rm", "-rf", "event.txt");
				fprintf(stderr,"rm 실패");
				exit(1);
			}

			// 세마포어 자원 삭제
			if (semctl(semid, 0, IPC_RMID, s_union) == -1) {
				printf( "semctl()-IPC_RMID Fail\n");
				return -1;
			}

			break;
		}

		// 세마포어 : close
		semop(semid, &mysem_close, 1);

		sleep(1);	// 1초 단위 확인
	}

	exit(0);
}

