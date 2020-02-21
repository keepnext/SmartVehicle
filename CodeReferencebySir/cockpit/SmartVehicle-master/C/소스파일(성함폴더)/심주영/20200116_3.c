#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	if (fork( ) == 0) {
		execl("b.out", NULL, NULL);
		fprintf(stderr,"첫 번째 실패");
		exit(1);
	}

	int child, status;
	child = wait(&status);
}

