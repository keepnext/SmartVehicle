#include <sys/types.h>
#include <wait.h>
#include <stdio.h>

void main()
{
	if (fork( ) == 0) {
		execl("smpcheck", NULL, NULL);
		
		exit(1);
	}
}
