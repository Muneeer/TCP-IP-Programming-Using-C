#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
void error_handling(char *message);

int main(int argc , char* argv[]) {

  int serv_sock,clnt_sock,i,str_len;
  char message[BUFF_SIZE];

  struct sockaddr_in serv_addr,clnt_addr;
  socklen_t clnt_addr_sz;

  if(argc!=2)
  {
    printf("Usage %s port\n",argv[0]);
  }
  serv_sock=socket(PF_INET,SOCK_STREAM,0);

  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=htons(atoi(argv[1]));

  if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
  {
    error_handling("bind() error");
  }

  if(listen(serv_sock,5)==-1)
  {
    error_handling("listen() error");
  }


  clnt_addr_sz=sizeof(clnt_addr);

for(i=0;i<5;i++)
{
  clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
  if(clnt_sock==-1){
    error_handling("accept() error");
  }
  printf("Total number of connected clients are : %d\n",i);
  while((str_len=read(clnt_sock,message,BUFF_SIZE))!=0)
  {
  	message[str_len]=0;
  	printf("You entered: %s",message);
  	write(clnt_sock,message,str_len);
  }

  close(clnt_sock);
}
printf("Total number of connected clients are : %d\n",i);
  
  close(serv_sock);
  
  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
