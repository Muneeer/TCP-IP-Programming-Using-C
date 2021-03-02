#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int sum=0;

void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	void * tr1_return;
	void *tr2_return;
	int tr1_r[]={1,5};
	int tr2_r[]={6,10};
	pthread_create(&t_id,NULL,thread_main,(void*)&tr1_r);
	pthread_create(&t_id,NULL,thread_main,(void*)&tr2_r);
	pthread_join(t_id,&tr1_return);
	pthread_join(t_id,&tr2_return);
	
	printf("Result 1 : %d\n",sum);
	//printf("Result 2 : %d\n",(((int*)tr1_return)+((int*)tr2_return));
	
	return 0;
}
void* thread_main(void *arg)
{
	int s=((int *)arg)[0];
	int e=((int *)arg)[1];
	//int cnt=*((int*)arg);
	//for(int i=((int*)arg)[0];i<((int*)arg)[1];i++)
	for(int i=s;i<=e;i++)
	{
		sum+=i;
	}
	
	return (void*)&sum;
}
