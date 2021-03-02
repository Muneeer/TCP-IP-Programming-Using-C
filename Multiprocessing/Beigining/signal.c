#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void timeout(int sig);
void keypressed(int sig);


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

void timeout(int sig)
{
	if(sig==SIGALRM)
		puts("TIME OUT\n");
	
	alarm(2);
}

void keypressed(int sig)
{
	if(sig==SIGINT)
		puts("KEY C is Pressed.!!!\n");
}
