#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
int main(){
	pid_t pid;

	printf("Parent process : pid = %d, ppid = %d\n", getpid(), getppid());

	pid = fork();

	if ( pid != 0 ) {/* parent process */
		printf("Parent process : pid = %d, ppid = %d\n", getpid(), getppid());
		printf("fork-child process : pid = %d\n", pid);

		exit(1);
	} else { /* child process */
		sleep(5);
		printf("child process : pid = %d, ppid = %d\n", getpid(), getppid());

		//execl("./","check_event", NULL, NULL);
		execl("/home/class/code/C/Work/exex/check_event","check_event", NULL, NULL);
	} /* parent & child process */

	printf("pid %d terminates.. \n", getpid()); 
}

