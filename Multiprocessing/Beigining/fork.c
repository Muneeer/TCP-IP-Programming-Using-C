#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	int lval=20;
	int gval=10;
	lval+=5;
	gval++;
	
	pid=fork();
	
	if(pid==0)
	{
		gval+=2;lval+=2;
		
		printf("Child Processes : [%d, %d]\n",gval,lval);
	}
	else{
	gval-=2;lval-=2;
	printf("Parent Processes : [%d, %d]\n",gval,lval);
	}
}
