#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 1024

void errorhandling(char *message);

int main(int argc,char *argv[]) {

char message[BUFF_SIZE];
  int ssock,csock,operands;

  struct sockaddr_in saddr,caddr;
  socklen_t caddrsize;

  if(argc!=2)
  {
    printf("port number of %s",argv[0]);
    exit(1);
  }
  ssock=socket(PF_INET, SOCK_STREAM, 0);

  memset(&saddr, 0, sizeof(saddr));

  saddr.sin_family=AF_INET;
  saddr.sin_addr.s_addr=htonl(INADDR_ANY);
  saddr.sin_port=htons(atoi(argv[1]));

  if(bind(ssock, (struct sockaddr *)&saddr,sizeof(saddr))==-1)
  {
    errorhandling("bind() error");
  }

  if(listen(ssock, 5)==-1)
  {
    errorhandling("listen() error");
  }

  caddrsize=sizeof(caddr);
  csock=accept(ssock, (struct sockaddr *)&caddr, &caddrsize);

  if(csock==-1)
  {
    errorhandling("accept() error");
  }

  printf("Connected!!\n");
  // for(int i=0;i<5;i++)
  // {
  //   printf("Client %d connected!!!\n",i+1);

  // }
  
  //int strlen=read(csock,message,sizeof(message));
  //message[strlen]=0;
  read(csock,operands,sizeof(operands));
  
  int arr[operands]
  
  printf("%s",message);

  printf("Hello World\n");
  return 0;
}

void errorhandling(char *message){
  fputs(message, stderr);
  fputs("\n",stderr);
  exit(1);
}
