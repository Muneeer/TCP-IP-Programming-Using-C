#include <stdio.h>
#include <unistd.h>

int main(void) {

  int pid=fork();

  if(pid==0)
  {
    printf("Hi i am child and my PID is %d\n",getpid());
  }else
  {
    printf("Hi i am the Parent and my PID is %d\n",getpid());
  }
  
  printf("Hello World\n");
  return 0;
}
