#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param=5;
	if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param)!=0){
		puts("Pthread Error...!!!");
		return -1;
	}
	
	sleep(10);
	puts("Main Ends!!!");
	return 0;
}
void* thread_main(void *arg)
{
	int i;
	int cnt=*((int*)arg);
	for(int i=0;i<cnt;i++)
	{
		puts("thread function");
		sleep(1);	
	}
	
	return NULL;
}
