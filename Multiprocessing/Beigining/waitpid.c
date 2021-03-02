#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	int status;
	
	pid=fork();
	printf("PID %d\n",pid);
	
	if(pid==0)
	{
		puts("Before Child sleeping\n");
		sleep(17);
		puts("Child sleeping\n");
		return 88;
	}
	else{
	while(!waitpid(-1,&status,WNOHANG)){
		
		sleep(3);
		puts("Sleeping for 3 sec\n");
	}
	if(WIFEXITED(status))
			printf("1st Child send : %d\n",WEXITSTATUS(status));
	}
}
