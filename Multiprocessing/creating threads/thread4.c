#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define NUM_THREAD 100



void* thread_inc(void *arg);
void* thread_dec(void *arg);
long long sum=0;

int main(int argc, char *argv[])
{
	pthread_t t_id[NUM_THREAD];
	
	void * tr1_return;
	void *tr2_return;
	int tr1_r[]={1,5};
	int tr2_r[]={6,10};
	printf("sizeof long long : %d\n",sizeof(long long));
	
	for(int i=0;i<NUM_THREAD;i++)
	{
		if(i%2)
			pthread_create(&(t_id[i]),NULL,thread_inc,NULL);
		else
			pthread_create(&(t_id[i]),NULL,thread_dec,NULL);
	}
	for(int i=0;i<NUM_THREAD;i++)
		pthread_join(t_id[i],NULL);
	
	printf("Result : %lld\n",sum);
	
	return 0;
}
void* thread_inc(void *arg)
{
	int s=((int *)arg)[0];
	int e=((int *)arg)[1];
	//int cnt=*((int*)arg);
	//for(int i=((int*)arg)[0];i<((int*)arg)[1];i++)
	for(int i=0;i<50000000;i++)
	{
		sum+=i;
	}
	
	return NULL;
}
void* thread_dec(void *arg)
{
	
	for(int i=0;i<50000000;i++)
	{
		sum-=i;
	}
	
	return NULL;
}
