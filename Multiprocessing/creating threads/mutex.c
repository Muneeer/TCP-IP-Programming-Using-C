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
	
	//int cnt=*((int*)arg);
	//for(int i=((int*)arg)[0];i<((int*)arg)[1];i++)
	//pthread_mutex_lock(&mutex)
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
