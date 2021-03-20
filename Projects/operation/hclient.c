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
  int ssock,operands;

  struct sockaddr_in saddr;

  if(argc!=3)
  {
    printf("port number of %s",argv[0]);
    exit(1);
  }
  ssock=socket(PF_INET, SOCK_STREAM, 0);

  memset(&saddr, 0, sizeof(saddr));

  saddr.sin_family=AF_INET;
  saddr.sin_addr.s_addr=inet_addr(argv[1]);
  saddr.sin_port=htons(atoi(argv[2]));

  
  if(connect(ssock,(struct sockaddr* )&saddr,sizeof(saddr))==-1)
  {
    errorhandling("connect() error");
  }
  printf("Client Connected!! to server!!!\n");
  // for(int i=0;i<5;i++)
  // {
  //   printf("Client %d connected!!!\n",i+1);

  // }
  
    /*fputs("Enter a message: ",stdout);
    fgets(message, BUFF_SIZE, stdin); */
    
    printf("Enter the number of operands : ");
    scanf("%d",&operands);
    write(ssock,&operands,strlen(operands)
    
    write(ssock,message,strlen(message));
  

  printf("Hello World\n");
  return 0;
}

void errorhandling(char *message){
  fputs(message, stderr);
  fputs("\n",stderr);
  exit(1);
}
