#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h> 


#define FILE_NAME "event"
#define FILE_NAME_WITH_PATH "./event"

void read_file(const char *filename);
void check_file_gen(void);
static int semid;

union snum
{
	int val;
};

struct sembuf mysem_open = {0, -1, SEM_UNDO};
struct sembuf mysem_close = {0, 1, SEM_UNDO};

int main( )
{
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

    while(1) {
	    check_file_gen();

        //sleep(5);
        usleep(100);
    }

	return 0;
}

void check_file_gen(void)
{
	char strPath[] = { FILE_NAME_WITH_PATH };
	// sem op
	semop(semid, &mysem_open, 1);
	int nResult = access( strPath, 0 );

	if( nResult == 0 )
	{
		printf( "지정한 경로에 파일⁄폴더가 존재 합니다.\n" );

        read_file(strPath);
	}
	else if( nResult == -1 )
	{
		printf( "지정한 경로에 파일⁄폴더가 존재하지 않습니다.\n" );
	}

    // sem close
	semop(semid, &mysem_close, 1);
}

void read_file(const char *filename)
{
    FILE *fp;
    //char *line;
    char line[256];
	fp = fopen(filename, "rt");
    printf("\n");

    while (fread(line, 1, 256, fp) > 0) 
	{
		printf("%s\n", line);
	}

    fclose(fp);
}