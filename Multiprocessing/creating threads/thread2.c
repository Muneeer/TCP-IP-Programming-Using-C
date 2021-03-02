#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param=5;
	void * thr_return;
	if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param)!=0){
		puts("Pthread Error...!!!");
		return -1;
	};
	
	if(pthread_join(t_id,&thr_return)!=0)
	{
		puts("pthread_join() error");
		return -1;
	}
	
	puts("THread returned message : %s\n",(char * )thr_return);
	free(thr_return);
	return 0;
}
void* thread_main(void *arg)
{
	int i;
	int cnt=*((int*)arg);
	char *msg=(char *)malloc(sizeof(char)*50);
	strcpy(msg,"Hello i am thread...!!\n");
	for(int i=0;i<cnt;i++)
	{
		puts("thread function");
		sleep(1);	
	}
	
	return (void *)msg;
	
	return NULL;
}
