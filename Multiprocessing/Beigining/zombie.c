#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	
	pid=fork();
	
	if(pid==0)
	{
		printf("Hello I am Child Process.\n");
		printf("Child Process Ends.!!!\n");
	}
	else{
	printf("Hello I am Parent Process PID : %d\n",pid);
	sleep(30);
	printf("Parent Process Ends.!!!\n");
	}
}
