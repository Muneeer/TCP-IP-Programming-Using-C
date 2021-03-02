#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void read_childprocess(int sig);


int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM,timeout);
	signal(SIGINT,keypressed);
	
	alarm(2);
	
	for(i=0;i<3;i++)
	{
		puts("wait...\n");
		sleep(100);
	}
}
void read_childprocess(int sig)
{
	int status;
	
	pid_t id=waitpid(-1,&status,WNOHANG);
	
	
	
	if(WIFEXIT(status))
	{
		printf("Process Removed %d!!!\n",id);
		printf("Child sends %d!!!\n",WEXITSTATUS(status));
	}
}
