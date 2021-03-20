#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#define BUFF_SIZE 1024

void error_handling(char *message);

int main() {

  int serv_sock,str_len,recv_len,recv_cnt;
  struct sockaddr_in serv_addr;
  char message[BUFF_SIZE];


  serv_sock=socket(PF_INET,SOCK_STREAM,0);


  memset(&serv_addr,0,sizeof(serv_addr));

  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr("192.168.241.128");
  serv_addr.sin_port=htons(8080);

 if(connect(serv_sock, (struct sockaddr* )&serv_addr,sizeof(serv_addr))==-1)
   error_handling("connect() error");
while(1)
{
  fputs("Enter a message (q|Q to quit) : ",stdout);
  fgets(message, BUFF_SIZE, stdin);

  if(!strcmp(message,"q\n") || !strcmp(message, "Q\n"))
  {
    break;
  }

  write(serv_sock, message, strlen(message));
  str_len=read(serv_sock, message, BUFF_SIZE-1);
  message[str_len]=0;
  printf("Server : %s\n",message);

 }
 

close(serv_sock);



  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
