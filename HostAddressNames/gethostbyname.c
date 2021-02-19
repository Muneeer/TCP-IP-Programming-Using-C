#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc , char* argv[]) {

struct hostent *host;

  if(argc!=2)
  {
    printf("Usage %s addr\n",argv[0]);
    exit(1);
  }
  
  host=gethostbyname(argv[1]);
  
  if(!host)
  {
  	error_handling("gethost.... error");
  }
  
  
  //struct in_addr addr=htonl(INADDR_NONE);
  printf("Address INADDR_NONE %s\n",inet_ntoa(INADDR_NONE));
  printf("Official name : %s\n",host->h_name);
  
  for(int i=0;host->h_aliases[i];i++)
  	printf("Aliases : %d : %s\n",i+1,host->h_aliases[i]);
  
  printf("Address type : %s.\n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");
  
 for(int i=0;host->h_addr_list[i];i++)
 	printf("IP addr %d: %s\n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
  
  

  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
