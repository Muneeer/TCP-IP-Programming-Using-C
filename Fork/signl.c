#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
void timeout(int sig);
void keypressed(int sig);
int main()
{

  signal(SIGALRM, timeout);
  signal(SIGINT, keypressed);

  alarm(2);

  for(int i=0;i<5;i++)
  {
    printf("Wait....in the loop\n");
    sleep(100);
  }


}

void timeout(int sig){

  if(sig==SIGALRM)
    {
      printf("Times out!!\n");
    }
    alarm(2);

}
void keypressed(int sig){
  printf("Key is pressed!!!\n");
  
}
