#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	int status;
	
	pid=fork();
	
	if(pid==0)
	{
		return 3;
	}
	else{
	printf("1st Child PID : %d\n",pid);
	pid=fork();
	if(pid==0)
		return 7;
	else{
		printf("2nd Child PID : %d\n",pid);
		wait(&status);
		if(WIFEXITED(status))
			printf("1st Child send : %d\n",WEXITSTATUS(status));
		
		wait(&status);
		if(WIFEXITED(status))
			printf("2nd Child send : %d\n",WEXITSTATUS(status));
		
		sleep(30);
	}
	}
}
